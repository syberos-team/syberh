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
class Build {
    constructor(appPath, config) {
        this.conf = {};
        // 是否支持cdb
        this.isSupportCdb = false;
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
        this.conf = Object.assign({}, this.conf, config);
        if (log_1.log.isVerboseEnabled()) {
            log_1.log.verbose('Build constructor(%s, %j)', appPath, config);
            log_1.log.verbose('配置参数:%j', this.conf);
        }
        this.pdkRootPath = helper.locatePdk();
        this.targetName = helper.getTargetName(this.appPath, this.conf.adapter);
    }
    /**
     * 开始编译
     */
    buildSop() {
        return __awaiter(this, void 0, void 0, function* () {
            log_1.log.verbose('Build buildSop()');
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
     * 开始编译， 并在设备上运行
     */
    start() {
        return __awaiter(this, void 0, void 0, function* () {
            console.log(chalk_1.default.green('开始编译'));
            log_1.log.verbose('Build start()');
            log_1.log.verbose('appPath:%s, conf:%j', this.appPath, this.conf);
            // 执行编译
            yield this.buildSop();
            // 安装sop
            yield this.installSop();
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
    copywww(appPath = this.appPath) {
        return __awaiter(this, void 0, void 0, function* () {
            console.log(chalk_1.default.green('准备拷贝www目录'));
            log_1.log.verbose('Build copywww(%s)', appPath);
            // const projectName = getProjectName(appPath)
            const wwwPath = path.join(appPath, index_1.default.SOURCE_DIR);
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
            const { adapter } = this.conf;
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
            // 检查是否支持cdb
            this.checkCdb();
            // 非模拟器，支持cdb
            if (!this.useSimulator && this.isSupportCdb) {
                // 发送
                this.cdbSop(sopPath);
                // 安装
                this.cdbInstallSop(path.basename(sopPath));
                // 启动
                this.cdbStartApp();
            }
            else {
                // 发送
                this.scpSop(adapterConfig.ip, adapterConfig.port, sopPath);
                // 安装
                this.sshInstallSop(adapterConfig.ip, adapterConfig.port, path.basename(sopPath));
                // 启动
                this.sshStartApp(adapterConfig.ip, adapterConfig.port);
            }
        });
    }
    checkCdb() {
        log_1.log.verbose('Build checkCdb()');
        // 安装至模拟器时，不使用cdb
        if (this.useSimulator) {
            return;
        }
        const cdbPath = this.locateCdb();
        log_1.log.verbose('%s devices', cdbPath);
        const cdbCmd = `${cdbPath} devices`;
        log_1.log.verbose('执行：', cdbCmd);
        let result = shelljs.exec(`${cdbPath} devices`);
        log_1.log.verbose('执行结果：', result);
        // 出现no permissions时，需要重启cdb服务
        if (result.stdout.indexOf('no permissions') > 0) {
            console.log(chalk_1.default.yellow('正在重启cdb服务，启动过程中可能需要输入当前用户的密码...'));
            let cmd = `${cdbPath} kill-server`;
            log_1.log.verbose('执行：', cmd);
            shelljs.exec(cmd);
            cmd = `sudo ${cdbPath} start-server`;
            log_1.log.verbose('执行：', cmd);
            shelljs.exec(cmd);
            cmd = `${cdbPath} devices`;
            log_1.log.verbose('执行：', cmd);
            result = shelljs.exec(cmd);
        }
        this.isSupportCdb = result.stdout.indexOf('-SyberOS') > 0;
        const lastIdx = result.stdout.indexOf('-SyberOS');
        const prefixSub = result.stdout.substring(0, lastIdx + 8);
        const firstIdx = prefixSub.lastIndexOf('\n');
        this.cdbDevice = result.stdout.substring(firstIdx + 1, lastIdx + 8);
        log_1.log.verbose('isSupportCdb:%s, cdbDevice:%s', this.isSupportCdb, this.cdbDevice);
    }
    scpSop(ip, port, sopPath) {
        log_1.log.verbose('Build scpSop(%s, %d, %s)', ip, port, sopPath);
        console.log(chalk_1.default.green('准备发送sop包'));
        log_1.log.verbose('ip:%s, port:%d, sopPath:%s', ip, port, sopPath);
        // 非模拟器，支持cdb
        if (!this.useSimulator && this.isSupportCdb) {
            const cdbPath = this.locateCdb();
            const cdbPushCmd = `${cdbPath} -s ${this.cdbDevice} push -p ${sopPath} /tmp`;
            log_1.log.verbose('执行：', cdbPushCmd);
            shelljs.exec(cdbPushCmd);
        }
        else {
            const cmd = `expect ${helper.locateScripts('scp-sop.sh')} ${ip} ${port} ${sopPath}`;
            log_1.log.verbose('执行：', cmd);
            shelljs.exec(cmd);
        }
    }
    cdbSop(sopPath) {
        log_1.log.verbose('Build cdbSop(%s)', sopPath);
        const cdbPushCmd = `${this.locateCdb()} -s ${this.cdbDevice} push -p ${sopPath} /tmp`;
        log_1.log.verbose('执行：', cdbPushCmd);
        shelljs.exec(cdbPushCmd);
    }
    sshInstallSop(ip, port, filename) {
        log_1.log.verbose('Build sshInstallSop(%s, %d, %s)', ip, port, filename);
        console.log(chalk_1.default.green('准备安装sop包'));
        log_1.log.verbose(filename);
        const nameSplit = filename.split('-');
        const cmd = `expect ${helper.locateScripts('ssh-install-sop.sh')} ${ip} ${port} ${nameSplit[0]} ${filename}`;
        log_1.log.verbose('执行：', cmd);
        shelljs.exec(cmd);
    }
    cdbInstallSop(filename) {
        log_1.log.verbose('Build cdbInstallSop(%s)', filename);
        console.log(chalk_1.default.green('准备安装sop包'));
        log_1.log.verbose(filename);
        const cmd = `expect ${helper.locateScripts('cdb-install-sop.sh')} ${this.locateCdb()} ${this.cdbDevice} ${filename}`;
        log_1.log.verbose('执行：', cmd);
        shelljs.exec(cmd);
    }
    sshStartApp(ip, port) {
        log_1.log.verbose('Build sshStartApp(%s, %d)', ip, port);
        const { sopid, projectName } = this.conf;
        console.log(chalk_1.default.green('准备启动app'));
        log_1.log.verbose('%s:%s:uiapp', sopid, projectName);
        const cmd = `expect ${helper.locateScripts('ssh-start-app.sh')} ${ip} ${port} ${sopid} ${projectName}`;
        log_1.log.verbose('执行：', cmd);
        shelljs.exec(cmd);
    }
    cdbStartApp() {
        log_1.log.verbose('Build cdbStartApp()');
        const { sopid, projectName } = this.conf;
        console.log(chalk_1.default.green('准备启动app'));
        log_1.log.verbose('%s:%s:uiapp', sopid, projectName);
        const cmd = `expect ${helper.locateScripts('cdb-start-app.sh')} ${this.locateCdb()} ${this.cdbDevice} ${sopid} ${projectName}`;
        log_1.log.verbose('执行：', cmd);
        shelljs.exec(cmd);
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
        const exConfig = Buffer.from(JSON.stringify(this.conf), 'utf8').toString('hex');
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
            console.log(chalk_1.default.green(`getCpu() stdout :${ret}`));
            log_1.log.verbose(chalk_1.default.green(`getCpu() stdout :${ret}`));
        }
        catch (e) {
            log_1.log.error('----------stdout', e);
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
    /**
     * 查找cdb路径
     */
    locateCdb() {
        log_1.log.verbose('Build locateCdb()');
        return path.join(this.pdkRootPath, 'targets', this.targetName, 'usr', 'lib', 'qt5', 'bin', 'cdb');
    }
}
exports.default = Build;
