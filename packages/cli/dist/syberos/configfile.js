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
const os = require("os");
const fs = require("fs-extra");
const readline = require("readline");
const path = require("path");
const shelljs = require("shelljs");
const log_1 = require("../util/log");
const homedir = os.homedir();
class Qtversions {
    constructor() {
        this.sdkKeyword = 'sdk-install-path=';
        this.path = this.getPath(homedir);
    }
    /**
     * 获取.config/qtversions.conf文件路径，若文件不存在会创建该文件
     */
    getPath(home) {
        const dirPath = path.join(home, '.config');
        if (!fs.pathExistsSync(dirPath)) {
            fs.mkdirsSync(dirPath);
        }
        const filePath = path.join(dirPath, 'qtversions.conf');
        if (!fs.existsSync(filePath)) {
            fs.createFileSync(filePath);
        }
        return filePath;
    }
    setPath(path) {
        this.path = path;
    }
    readReplace(key, installPath) {
        log_1.log.verbose('读取：', this.path);
        // key 是否存在文件中
        let isKeyExist = false;
        const lines = [];
        return new Promise((resolve) => {
            readline.createInterface({
                input: fs.createReadStream(this.path)
            }).on('line', line => {
                if (line.startsWith(key)) {
                    isKeyExist = true;
                    lines.push(key + installPath);
                }
                else {
                    lines.push(line);
                }
            }).on('close', () => {
                // 文件无内容或者没有对应的key时，添加
                if (lines.length === 0 || !isKeyExist) {
                    lines.push(key + installPath);
                }
                log_1.log.verbose('写入内容：%j', lines);
                resolve(lines);
            });
        });
    }
    readLine(startsWith) {
        log_1.log.verbose('读取行：', this.path);
        let lineContent;
        return new Promise((resolve) => {
            readline.createInterface({
                input: fs.createReadStream(this.path)
            }).on('line', line => {
                if (line.startsWith(startsWith)) {
                    lineContent = line;
                }
            }).on('close', () => {
                log_1.log.verbose('读取行内容：%s', lineContent);
                resolve(lineContent);
            });
        });
    }
    readLines() {
        return __awaiter(this, void 0, void 0, function* () {
            log_1.log.verbose('读取所有行：', this.path);
            const lines = [];
            return new Promise((resolve) => {
                readline.createInterface({
                    input: fs.createReadStream(this.path)
                }).on('line', line => {
                    lines.push(line);
                }).on('close', () => {
                    log_1.log.verbose('读取行内容：%j', lines);
                    resolve(lines);
                });
            });
        });
    }
    flush(lines) {
        fs.writeFileSync(this.path, lines.join('\n'));
    }
    sdkInstallPath(installPath) {
        const key = this.sdkKeyword;
        this.readReplace(key, installPath).then(lines => {
            this.flush(lines);
        });
    }
    targetInstallPath(targetName, installPath) {
        const key = targetName + '=';
        const qmakePath = path.join(installPath, 'targets', targetName, 'usr/lib/qt5/bin/qmake');
        this.readReplace(key, qmakePath).then(lines => {
            this.flush(lines);
        });
    }
    getSdkInstallPath() {
        return __awaiter(this, void 0, void 0, function* () {
            const startsWith = 'sdk-install-path=';
            const line = yield this.readLine(startsWith);
            if (line) {
                return line.substring(startsWith.length, line.length);
            }
            return '';
        });
    }
    getTargetInstallPath(targetName) {
        return __awaiter(this, void 0, void 0, function* () {
            const startsWith = targetName + '=';
            const line = yield this.readLine(startsWith);
            if (line) {
                return line.substring(startsWith.length, line.length);
            }
            return '';
        });
    }
    getTargetInstallPaths() {
        return __awaiter(this, void 0, void 0, function* () {
            const lines = yield this.readLines();
            const paths = [];
            for (const line of lines) {
                if (!line) {
                    continue;
                }
                if (line.startsWith(this.sdkKeyword)) {
                    continue;
                }
                const lineArray = line.split('=');
                if (lineArray && lineArray.length >= 2) {
                    paths.push(lineArray[1]);
                }
            }
            return paths;
        });
    }
    getInstallTargets() {
        return __awaiter(this, void 0, void 0, function* () {
            const lines = yield this.readLines();
            const targetPaths = [];
            for (const line of lines) {
                if (!line) {
                    continue;
                }
                if (line.startsWith(this.sdkKeyword)) {
                    continue;
                }
                const lineArray = line.split('=');
                if (lineArray && lineArray.length >= 2) {
                    targetPaths.push({
                        name: lineArray[0],
                        path: lineArray[1]
                    });
                }
            }
            return targetPaths;
        });
    }
    getTargetNames() {
        return __awaiter(this, void 0, void 0, function* () {
            const targetPaths = yield this.getInstallTargets();
            const targetNames = [];
            for (const targetPath of targetPaths) {
                targetNames.push(targetPath.name);
            }
            return targetNames;
        });
    }
}
class Scratchbox2 {
    constructor() {
        this.path = this.getPath(homedir);
    }
    getPath(home) {
        const dirPath = path.join(home, '.scratchbox2');
        if (!fs.pathExistsSync(dirPath)) {
            fs.mkdirsSync(dirPath);
        }
        return dirPath;
    }
    /**
     * 拷贝scratchbox2目录
     * @param targetName
     * @param installPath
     */
    copyDir(targetName, installPath) {
        const src = path.join(installPath, 'targets', targetName, 'scratchbox2/*');
        shelljs.cp('-r', src, this.path);
    }
}
exports.qtversions = new Qtversions();
exports.scratchbox2 = new Scratchbox2();
