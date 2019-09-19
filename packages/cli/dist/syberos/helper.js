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
const constants_1 = require("../util/constants");
const index_1 = require("../util/index");
const shelljs = require("shelljs");
const chalk_1 = require("chalk");
const configfile_1 = require("./configfile");
/**
 *  读取project.config.json配置文件
 * @param appPath
 * @return project.config.json
 */
exports.getProjectConfig = (appPath) => {
    try {
        return fs.readJSONSync(path.join(appPath, constants_1.PROJECT_CONFIG));
    }
    catch (error) {
        console.error('读取配置文件失败', JSON.stringify(error));
        throw new Error(`${constants_1.PROJECT_CONFIG} 不存在`);
    }
};
/**
 * 获取项目名称
 * @param appPath
 * @return string
 */
exports.getProjectName = (appPath) => {
    const { projectName } = exports.getProjectConfig(appPath);
    return projectName;
};
/**
 * 获取ProjectConfig 配置文件中的target
 * @param appPath
 * @param targetName
 * @return string 返回target name
 *
 */
exports.getTargetName = (appPath, adapter) => {
    const projectConfig = exports.getProjectConfig(appPath);
    if (adapter === "simulator" /* SIMULATOR */) {
        return projectConfig.targetSimulator;
    }
    if (adapter === "device" /* DEVICE */) {
        return projectConfig['target'];
    }
    return projectConfig['target'];
    // throw new Error(`${PROJECT_CONFIG} 配置文件未找到`)
};
/**
 * 主进程休眠
 * @param ms 休眠时长（毫秒）
 */
exports.sleep = (ms) => {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            try {
                resolve(1);
            }
            catch (e) {
                reject(e);
            }
        }, ms);
    });
};
/**
 * 获取当前用户home目录下的子目录的路径
 * @param subDirs home目录下的子目录名
 */
exports.homeSubPath = (...subDirs) => {
    const { stdout } = shelljs.exec(`env | grep ^HOME= | cut -c 6-`);
    const subDirPath = path.join(stdout.trim(), ...subDirs);
    const existe = fs.pathExists(subDirPath);
    if (!existe) {
        throw new Error(`根目录下未找到${path.join(...subDirs)}目录`);
    }
    return subDirPath;
};
/**
 * 查找pdk根目录路径
 */
exports.locateSdk = () => {
    return configfile_1.qtversions.getSdkInstallPath();
};
exports.locateAllTarget = () => {
    return configfile_1.qtversions.getTargetInstallPaths();
};
exports.locateIde = () => {
    return exports.homeSubPath('SyberOS-SDK');
};
/**
 * 查找sh脚本路径
 * @param shFilename sh脚本文件吗
 */
exports.locateScripts = (shFilename) => {
    return path.join(index_1.getRootPath(), 'scripts', shFilename);
};
/**
 * 启动模拟器
 * @param port  模拟器ssh端口，默认5555
 */
exports.startvm = (port = 5555) => __awaiter(this, void 0, void 0, function* () {
    const emulatorPath = path.join(exports.locateIde(), 'emulator');
    console.log(`模拟器<${port}>：${emulatorPath}`);
    const pid = shelljs.exec('pgrep "emulator-x86"');
    if (pid.trim()) {
        console.log(chalk_1.default.blue(`模拟器正在运行[pid=${pid.trim()}]`));
        return;
    }
    const result = shelljs.exec(`${exports.locateScripts('startvm.sh')} ${emulatorPath} ${port || ''}`);
    if (result.code === 1) {
        yield exports.sleep(2000);
        console.log(chalk_1.default.blue(`模拟器已启动[pid=${shelljs.exec('pgrep "emulator-x86"').trim()}]`));
    }
    else if (result.code === 2) {
        console.log(chalk_1.default.red('启动模拟器失败'));
    }
});
