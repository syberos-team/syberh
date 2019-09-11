"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const chokidar = require("chokidar");
const log_1 = require("../util/log");
const file_1 = require("../util/file");
/**
 * 文件监控服务
 */
class Watcher {
    constructor(server, path) {
        // 更新的文件列表
        this.files = [];
        // 定时器时长
        this.timer = 1500;
        if (!server) {
            log_1.default.error('socket server is undefind');
            throw new Error('socket server is undefind');
        }
        this.server = server;
        if (Array.isArray(path)) {
            path.forEach(dirPath => {
                this.watch(dirPath);
            });
        }
        else if (typeof path === 'string') {
            this.watch(path);
        }
    }
    addFiles(filePath) {
        if (this.files.indexOf(filePath) >= 0) {
        }
        else {
            this.files.push(filePath);
        }
    }
    watch(dirPath) {
        const watcher = chokidar.watch(dirPath, {
            ignored: /(^|[/\\])\../,
            persistent: true,
            ignoreInitial: true
        });
        // Add event listeners.
        watcher
            .on('add', path => {
            log_1.default.verbose(`File ${path} has been added`);
            this.addFiles(path);
            this.listenerDir(dirPath);
        })
            .on('change', path => {
            log_1.default.verbose(`File ${path} has been changed`);
            this.addFiles(path);
            this.listenerDir(dirPath);
        })
            .on('unlink', path => {
            log_1.default.verbose(`File ${path} has been removed`);
            const fs = [];
            file_1.readDirSync(dirPath, fs, fileList => {
                this.files = [...this.files, ...fileList];
                log_1.default.verbose('removed files length:', this.files.length);
                this.listenerDir(dirPath);
            });
        });
        // More possible events.
        watcher
            .on('addDir', path => {
            log_1.default.verbose(`Directory ${path} has been added`);
            const fs = [];
            file_1.readDirSync(path, fs, fileList => {
                this.files = [...this.files, ...fileList];
                log_1.default.verbose('Directory files length:', this.files.length);
                this.listenerDir(dirPath);
            });
        })
            .on('unlinkDir', path => {
            log_1.default.verbose(`Directory ${path} has been removed`);
            const fs = [];
            file_1.readDirSync(dirPath, fs, fileList => {
                this.files = [...this.files, ...fileList];
                log_1.default.verbose('Directory unlinkDir files length:', this.files.length);
                this.listenerDir(dirPath);
            });
        })
            .on('error', error => {
            log_1.default.verbose(`Watcher error: ${error}`);
            // listenerDir(wss, dirPath)
        })
            .on('ready', () => {
            log_1.default.verbose('Initial scan complete. Ready for changes');
            // listenerDir(wss, dirPath)
        })
            .on('raw', (event, path, details) => {
            // internal
            log_1.default.verbose('Raw event info:', event, path, details);
        });
    }
    listenerDir(path) {
        log_1.default.verbose('----listenerDir', path);
        // 如果开始了,则删除
        if (this.setTimeoutTimer) {
            log_1.default.verbose('清除定时器');
            clearTimeout(this.setTimeoutTimer);
            this.setTimeoutTimer = undefined;
        }
        this.setTimeoutTimer = setTimeout(() => {
            log_1.default.verbose('setTimeoutTimer', this.setTimeoutTimer);
            this.server.writeFileToClients(this.files, () => {
                this.files = [];
            });
            clearTimeout(this.setTimeoutTimer);
            this.setTimeoutTimer = undefined;
        }, this.timer);
    }
}
exports.default = Watcher;
