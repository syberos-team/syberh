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
const helper = require("../syberos/helper");
const fs = require("fs-extra");
const shelljs = require("shelljs");
const path = require("path");
const log_1 = require("../util/log");
function buildReport(errors) {
    return __awaiter(this, void 0, void 0, function* () {
        return {
            desc: '检查SyberOS编译环境',
            lines: errors
        };
    });
}
function checkExpect() {
    return __awaiter(this, void 0, void 0, function* () {
        log_1.log.verbose('checkExpect()');
        const errorLines = [];
        const cmd = 'whereis expect';
        const { stdout } = shelljs.exec(cmd);
        log_1.log.verbose('stdout:', stdout);
        if (stdout.indexOf('/usr/bin/expect') === -1) {
            log_1.log.warn('未找到expect :', stdout);
            errorLines.push({
                desc: `expect 未安装`,
                valid: false,
                solution: `请执行升级命令:  sudo apt-get install expect`
            });
        }
        return errorLines;
    });
}
function checkSyberosPdk() {
    return __awaiter(this, void 0, void 0, function* () {
        log_1.log.verbose('checkSyberosPdk() start');
        const pdkPath = yield helper.locatePdk();
        const errorLines = [];
        if (!fs.pathExistsSync(pdkPath)) {
            errorLines.push({
                desc: '没有检查到Syberos-Pdk目录:' + pdkPath,
                valid: false,
                solution: '请重新安装sdk，并使用默认的安装路径，切勿修改sdk安装路径'
            });
            return errorLines;
        }
        if (!fs.existsSync(path.join(pdkPath, 'sdk', 'sdk-root', 'syberos-sdk-chroot'))) {
            errorLines.push({
                desc: '无效的Syberos-Pdk目录:' + pdkPath,
                valid: false,
                solution: '请重新安装sdk，并使用默认的安装路径，切勿修改sdk安装路径'
            });
        }
        return errorLines;
    });
}
function checkTarget() {
    return __awaiter(this, void 0, void 0, function* () {
        log_1.log.verbose('checkTarget() start');
        const pdkPath = yield helper.locatePdk();
        const errorLines = [];
        const targetPath = path.join(pdkPath, 'targets');
        if (!fs.pathExistsSync(targetPath)) {
            errorLines.push({
                desc: '没有检查到targets目录:' + targetPath,
                valid: false,
                solution: '请安装target，并使用默认的安装路径，切勿修改target安装路径'
            });
            return errorLines;
        }
        const dirs = fs.readdirSync(targetPath);
        if (!dirs || dirs.length < 1 || !dirs.some((d) => { return d.startsWith('target-'); })) {
            errorLines.push({
                desc: '未安装任何target',
                valid: false,
                solution: '请安装target，并使用默认的安装路径，切勿修改target安装路径'
            });
            return errorLines;
        }
        return errorLines;
    });
}
function checkSyberOSSDK() {
    return __awaiter(this, void 0, void 0, function* () {
        log_1.log.verbose('checkSyberOSSDK() start');
        const sdkPath = helper.locateSdk();
        log_1.log.verbose('sdkPath() sdkPath', sdkPath);
        const errorLines = [];
        if (!fs.pathExistsSync(sdkPath)) {
            errorLines.push({
                desc: '没有检查到SyberOS-SDK目录:' + sdkPath,
                valid: false,
                solution: '请重新安装SyberOS SDK'
            });
            return errorLines;
        }
        if (!fs.existsSync(path.join(sdkPath, 'ide', 'bin', 'qtcSyberIDE'))) {
            errorLines.push({
                desc: '无效的SyberOS-SDK目录:' + sdkPath,
                valid: false,
                solution: '请重新安装SyberOS SDK'
            });
        }
        return errorLines;
    });
}
function default_1() {
    return __awaiter(this, void 0, void 0, function* () {
        const errorLines = yield checkExpect();
        errorLines.push(...yield checkSyberosPdk());
        errorLines.push(...yield checkTarget());
        errorLines.push(...yield checkSyberOSSDK());
        return buildReport(errorLines);
    });
}
exports.default = default_1;
