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
const net = require("net");
const fs = require("fs-extra");
const chalk = require("chalk");
const uuid = require("uuid");
const ip = require("internal-ip");
const os = require("os");
const path = require("path");
const HttpServer_1 = require("./HttpServer");
const log_1 = require("../util/log");
var SendStatus;
(function (SendStatus) {
    // 等待
    SendStatus[SendStatus["WATING"] = 0] = "WATING";
    // 发送中
    SendStatus[SendStatus["PENDING"] = 1] = "PENDING";
    SendStatus[SendStatus["RESOLVE"] = 2] = "RESOLVE";
})(SendStatus || (SendStatus = {}));
/**
 * socket 服务端
 */
class Server {
    constructor(config = {}) {
        // uid
        this.uid = 0;
        // 默认配置
        this.conf = {
            port: 8080
        };
        // 发送队列
        this.queue = [];
        this.timer = null;
        // 客户端列表
        this.clients = [];
        this.conf = Object.assign({}, this.conf, config);
        // 设置待发送状态
        this.sendStatus = SendStatus.WATING;
        this.startServer();
    }
    /**
     * 启动socket服务
     */
    startServer() {
        this.server = net.createServer();
        this.server.on('listening', () => __awaiter(this, void 0, void 0, function* () {
            // 初始化ip地址
            const vhost = this.conf.host || (yield ip.v4());
            this.conf.host = vhost;
            const ifaces = os.networkInterfaces();
            Object.keys(ifaces).forEach(dev => {
                ifaces[dev].forEach(details => {
                    if (details.family === 'IPv4') {
                        log_1.default.info(chalk.default.green(`socket服务 ${details.address}:${this.conf.port}`));
                    }
                });
            });
        }));
        this.server.on('connection', () => {
            log_1.default.info(chalk.default.green('客户端链接'));
            this.startHttpServer();
        });
        this.server.on('close', () => {
            log_1.default.warn(chalk.default.red('dev-server服务端关闭'));
        });
        this.server.listen(this.conf.port);
        // 监听错误信息
        this.server.on('error', e => {
            if (e.code === 'EADDRINUSE') {
                log_1.default.error(chalk.default.red(`${this.conf.port}端口正被使用,请重新设置`));
            }
        });
        this.onConnections();
    }
    startHttpServer() {
        this.httpServer = new HttpServer_1.default();
    }
    /**
     * 保存客户端socket
     * @param socket
     */
    saveClient(socket) {
        return __awaiter(this, void 0, void 0, function* () {
            this.clients.push(socket);
        });
    }
    /**
     * 移除socket
     * @param socket
     */
    removeClient(socket) {
        return __awaiter(this, void 0, void 0, function* () {
            const { sid } = socket;
            for (let i = 0; i < this.clients.length; i += 1) {
                if (this.clients[i].sid === sid) {
                    this.clients.splice(i, 1);
                    break;
                }
            }
        });
    }
    onConnections(callback) {
        this.server.on('connection', (socket) => {
            Object.assign(socket, { sid: uuid() });
            this.saveClient(socket);
            socket.on('close', () => {
                this.removeClient(socket);
                console.log('syberos-dev-server:客户端 连接断开');
            });
            socket.on('end', () => {
                console.log('syberos-dev-server:客户端 end');
            });
            typeof callback === 'function' && callback(socket);
        });
    }
    /**
     * 添加到队列
     * @param filePath
     * @param callback
     */
    addQueue(filePath, callback) {
        log_1.default.verbose('队列等待中   addQueue:', filePath);
        if (this.queue.length > 0) {
            // 清空数组
            this.queue = [];
        }
        // 保存队列内容
        this.queue.push({ filePath, callback });
    }
    /**
     * 获取当前待传输内容
     */
    getQueue() {
        // 删除并返回第一个
        return this.queue.shift();
    }
    /**
     * 发送给所有客户端
     * @param fileList [] 文件列表
     * @param callback
     */
    writeFileToClients(fs, callback) {
        return __awaiter(this, void 0, void 0, function* () {
            log_1.default.verbose('Server writeFileToClients() ');
            log_1.default.verbose('files', fs.length);
            const fileList = [...fs];
            if (fileList.length === 0) {
                log_1.default.info('files', JSON.stringify(fileList));
                return;
            }
            if (this.sendStatus === SendStatus.PENDING) {
                // 当前状态发送中，加入队列等待
                this.addQueue(fileList);
                callback && callback(true);
                return;
            }
            // 设置问发送状态
            this.sendStatus = SendStatus.PENDING;
            const filePath = path.resolve('.');
            let count = 0;
            const { clients = [] } = this;
            const files = fileList;
            const splitFiles = [];
            for (let i = 0; i < files.length; i++) {
                const file = files[i];
                const nf = file.replace(filePath, '');
                log_1.default.verbose('nf', nf);
                splitFiles.push(nf);
            }
            log_1.default.info('----当前客户端数量:', clients.length);
            // console.log('----替换后的地址:', JSON.stringify(splitFiles))
            clients.forEach((socket) => __awaiter(this, void 0, void 0, function* () {
                this.uid += 1;
                // 获取下载服务地址
                const serverhost = this.httpServer.getUri();
                log_1.default.verbose('----serverhost:', serverhost);
                // 发送数据格式
                const fileHead = {
                    uid: this.uid,
                    server: serverhost,
                    files: splitFiles
                };
                yield this.write(socket, JSON.stringify(fileHead));
                count += 1;
            }));
            callback && callback(true);
            // 启动定时器扫描发送情况
            this.timer = setInterval(() => {
                if (count === clients.length) {
                    log_1.default.info('-----发送完成,发送数量', clients.length);
                    clearInterval(this.timer);
                    this.timer = null;
                    // 说明已经发送完成，开始检查队列
                    this.sendStatus = SendStatus.RESOLVE;
                    const queue = this.getQueue();
                    if (!queue) {
                        return;
                    }
                    this.writeFileToClients(queue.filePath, null);
                }
            }, 1000);
        });
    }
    readDirSync(dirPath, files = [], callback) {
        const pa = fs.readdirSync(dirPath);
        const that = this;
        pa.forEach(function (ele, index) {
            const info = fs.statSync(path.join(dirPath, ele));
            if (info.isDirectory()) {
                that.readDirSync(path.join(dirPath, ele), files, null);
            }
            else {
                const filePath = path.join(dirPath, ele);
                files.push(filePath);
            }
        });
        if (callback)
            callback(files);
    }
    /**
     * 获取当前链接
     * @param callback 回调方法
     */
    getConnections(callback) {
        this.server.getConnections(callback);
    }
    onEnd(socket, callback) {
        socket.on('end', () => {
            log_1.default.warn('connect end');
        });
    }
    onClose(callback) {
        this.server.on('close', () => {
            log_1.default.info('onClose');
            callback && callback();
        });
    }
    /**
     * 刷新发送soket数据
     * @param socket
     * @param buffer
     */
    write(socket, buffer) {
        return __awaiter(this, void 0, void 0, function* () {
            return new Promise(function (resole, reject) {
                socket.write(buffer, function () {
                    resole(true);
                });
            });
        });
    }
}
exports.default = Server;
