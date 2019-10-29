"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : new P(function (resolve) { resolve(result.value); }).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
const fs = require("fs-extra");
const path = require("path");
const shelljs = require("shelljs");
const os = require("os");
const chalk_1 = require("chalk");
const helper = require("../syberos/helper");
const index_1 = require("../config/index");
const log_1 = require("../util/log");
const sop = require("./sop");
const connect = require("./connect");
class Build {
    constructor(appPath, webPath, config) {
        // 日志级别
        this.devLog = process.env.DEV_LOG || 'info';
        this.conf = {};
        // 是否安装至模拟器
        this.useSimulator = false;
        // 设备网络配置
        this.adapterConfig = {
            device: {
                ip: '192.168.100.100',
                port: 22
            },
            simulator: {
                ip: 'localhost',
                port: 5555
            }
        };
        this.appPath = appPath;
        this.webPath = webPath;
        this.conf = Object.assign({}, this.conf, config);
        if (log_1.log.isVerboseEnabled()) {
            log_1.log.verbose('Build constructor(%s, %j)', appPath, webPath, config);
            log_1.log.verbose('配置参数:%j', this.conf);
        }
        this.targetName = helper.getTargetName(this.appPath, this.conf.adapter);
    }
    /**
     * 开始编译， 并在设备上运行
     */
    start() {
        return __awaiter(this, void 0, void 0, function* () {
            log_1.log.verbose('Build start()');
            this.pdkRootPath = yield helper.locateSdk();
            log_1.log.verbose('pdkRootPath:', this.pdkRootPath);
            // 检查设备连接
            this.checkConnect(this.pdkRootPath, this.targetName);
            console.log(chalk_1.default.green('开始编译'));
            log_1.log.verbose('appPath:%s, conf:%j', this.appPath, this.conf);
            // 执行编译
            yield this.buildSop();
            // 安装sop
            yield this.installSop();
        });
    }
    /**
     * 检查手机是否连接
     */
    checkConnect(pdkRootPath, targetName) {
        log_1.log.verbose('Build checkConnect(%s, %s)', pdkRootPath, targetName);
        const { adapter } = this.conf;
        if ("device" /* DEVICE */ !== adapter) {
            log_1.log.verbose('当前设备类型为：%s, 无须检查设备连接');
            return;
        }
        const checker = new connect.ConnectChecker(pdkRootPath, targetName);
        if (checker.isCdbEnabled() || checker.isSshEnabled(this.adapterConfig.device.ip, this.adapterConfig.device.port)) {
            return;
        }
        console.log(chalk_1.default.red('未检测到设备'));
        process.exit(0);
    }
    /**
     * 开始编译
     */
    buildSop() {
        return __awaiter(this, void 0, void 0, function* () {
            log_1.log.verbose('Build buildSop()');
            this.pdkRootPath = yield helper.locateSdk();
            // 1、生成编译目录
            this.mkdirBuild();
            // 2、拷贝www路径到模板下
            yield this.copywww();
            // 3、执行构建命令
            yield this.executeShell();
            if (this.conf.onlyBuildSop === true) {
                const cmd = "ls --file-type *.sop |awk '{print i$0}' i=`pwd`'/'";
                log_1.log.verbose('执行：', cmd);
                const { stdout } = shelljs.exec(cmd);
                log_1.log.verbose('执行结果：', stdout);
                const sopPath = stdout.trim();
                console.log(chalk_1.default.blue('打包完成，SOP包的位置是=>'), sopPath);
                shelljs.exit(0);
            }
        });
    }
    /**
     * 生成编译目录
     */
    mkdirBuild() {
        console.log(chalk_1.default.green('准备编译目录'));
        log_1.log.verbose('Build mkdirBuild()');
        const appPath = this.appPath;
        const { adapter, debug, onlyBuildSop } = this.conf;
        // 定义编译目录
        if (onlyBuildSop === true) {
            // 如果是只打SOP包， 目录名的设备名为 device
            this.buildDir = `${appPath}/.build-${"device" /* DEVICE */}-${this.targetName}${debug ? '-Debug' : ''}`;
        }
        else {
            this.buildDir = `${appPath}/.build-${adapter}-${this.targetName}${debug ? '-Debug' : ''}`;
        }
        if (!fs.pathExistsSync(this.buildDir)) {
            fs.mkdirsSync(this.buildDir);
        }
        shelljs.cd(this.buildDir);
        log_1.log.info('已创建编译目录：', this.buildDir);
    }
    /**
     * 拷贝www路径
     * @param appPath
     */
    copywww(appPath = this.appPath, webPath = this.webPath) {
        return __awaiter(this, void 0, void 0, function* () {
            console.log(chalk_1.default.green('准备拷贝www目录'));
            log_1.log.verbose('Build copywww(%s)', appPath);
            // const projectName = getProjectName(appPath)
            const wwwPath = path.join(appPath, webPath || index_1.default.SOURCE_DIR);
            // 模板目录
            const syberosPath = path.join(appPath, 'platforms', 'syberos', 'app', 'www');
            try {
                yield fs.emptyDir(syberosPath);
                // 拷贝
                yield fs.copy(wwwPath, syberosPath);
            }
            catch (err) {
                log_1.log.error(chalk_1.default.red(err));
                return;
            }
            log_1.log.info('已拷贝www目录，From：', wwwPath, ' To：', syberosPath);
        });
    }
    /**
     * 执行构建脚本
     */
    executeShell() {
        return __awaiter(this, void 0, void 0, function* () {
            log_1.log.verbose('Build executeShell()');
            console.log(chalk_1.default.green('准备执行编译指令'));
            // kchroot qmake
            this.execKchroot(this.qmakeCommand());
            // kchroot make
            this.execKchroot(this.makeCommand());
            // kchroot buildPkg
            this.execKchroot(this.buildPkgCommand());
        });
    }
    /**
     * 安装sop包
     */
    installSop() {
        return __awaiter(this, void 0, void 0, function* () {
            log_1.log.verbose('Build installSop()');
            console.log(chalk_1.default.green('开始安装sop包...'));
            const { adapter, sopid, projectName } = this.conf;
            let adapterConfig;
            // 检查安装至模拟器还是真机
            if ("device" /* DEVICE */ === adapter) {
                adapterConfig = this.adapterConfig.device;
            }
            else if ("simulator" /* SIMULATOR */ === adapter) {
                adapterConfig = this.adapterConfig.simulator;
                this.useSimulator = true;
            }
            else {
                throw new Error('adapter类型错误');
            }
            const cmd = "ls --file-type *.sop |awk '{print i$0}' i=`pwd`'/'";
            log_1.log.verbose('执行：', cmd);
            const { stdout } = shelljs.exec(cmd);
            log_1.log.verbose('执行结果：', stdout);
            const sopPath = stdout.trim();
            // 启动虚拟机
            if ("simulator" /* SIMULATOR */ === adapter) {
                console.log(chalk_1.default.green('准备启动模拟器'));
                yield helper.startvm();
            }
            const cdbSop = new sop.CdbSop(this.pdkRootPath, this.targetName, sopid, projectName);
            // 非模拟器，支持cdb
            if (!this.useSimulator && cdbSop.isSupportCdb()) {
                // 发送
                cdbSop.send(sopPath);
                // 安装
                cdbSop.install(path.basename(sopPath));
                // 启动
                cdbSop.startApp();
            }
            else {
                const sshSop = new sop.SshSop(adapterConfig.ip, adapterConfig.port, sopid, projectName);
                // 发送
                sshSop.send(sopPath);
                // 安装
                sshSop.install(path.basename(sopPath));
                // 启动
                sshSop.startApp();
            }
        });
    }
    execKchroot(subCommand = '') {
        log_1.log.verbose('Build execKchroot()', subCommand);
        const { adapter, onlyBuildSop } = this.conf;
        const kchroot = this.locateKchroot();
        let cmd = '';
        if ("device" /* DEVICE */ === adapter) {
            // 真机
            cmd += `${kchroot} 'sb2 -t ${this.targetName} -R'`;
        }
        else if ("simulator" /* SIMULATOR */ === adapter) {
            // 模拟器
            cmd += `${kchroot} exec_${this.targetName}`;
        }
        else if (onlyBuildSop === true) {
            // 打SOP包， 和真机命令一样
            cmd += `${kchroot} 'sb2 -t ${this.targetName} -R'`;
        }
        else {
            throw new Error('adapter类型错误');
        }
        if (cmd) {
            if (subCommand) {
                cmd += ` '${subCommand}'`;
            }
            log_1.log.verbose('执行：', cmd);
            shelljs.exec(cmd);
        }
    }
    qmakeCommand() {
        log_1.log.verbose('Build qmakeCommand()');
        const { debug } = this.conf;
        const qmake = this.locateQmake();
        const syberosPro = this.locateSyberosPro();
        const qmakeConfig = debug ? 'qml_debug' : 'release';
        const exConfigObj = Object.assign({}, this.conf);
        exConfigObj.DEV_LOG = this.devLog;
        log_1.log.verbose('扩展参数：%j', exConfigObj);
        const exConfig = Buffer.from(JSON.stringify(exConfigObj), 'utf8').toString('hex');
        return `${qmake} ${syberosPro} -r -spec linux-g++ CONFIG+=${qmakeConfig} EX_CONFIG=${exConfig}`;
    }
    makeCommand() {
        log_1.log.verbose('Build makeCommand()');
        const cpu = this.getCpu();
        const cmd = `/usr/bin/make -j${cpu} `;
        log_1.log.verbose('Build makeCommand() cmd:', cmd);
        return cmd;
    }
    buildPkgCommand() {
        log_1.log.verbose('Build buildPkgCommand()');
        const syberosPro = this.locateSyberosPro();
        return `buildpkg ${syberosPro}`;
    }
    /**
     * 获取CUP进程数
     */
    getCpu() {
        log_1.log.verbose('Build getCpu()');
        let ret = 4;
        try {
            ret = os.cpus().length;
            log_1.log.verbose(chalk_1.default.green(`getCpu() length :${ret}`));
        }
        catch (e) {
            log_1.log.error('getCpu', e);
        }
        return ret;
    }
    /**
     * 查找kchroot路径
     */
    locateKchroot() {
        log_1.log.verbose('Build locateKchroot()');
        return path.join(this.pdkRootPath, 'sdk', 'script', 'kchroot');
    }
    /**
     * 查找qmake路径
     */
    locateQmake() {
        log_1.log.verbose('Build locateQmake()');
        return path.join(this.pdkRootPath, 'targets', this.targetName, 'usr', 'lib', 'qt5', 'bin', 'qmake');
    }
    /**
     * 查找项目中的syberos.pro文件路径
     */
    locateSyberosPro() {
        log_1.log.verbose('Build locateSyberosPro()');
        return path.join(this.appPath, 'platforms', 'syberos', 'app.pro');
    }
}
exports.default = Build;
