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
const express = require("express");
const fs = require("fs-extra");
const bodyParser = require("body-parser");
const path = require("path");
const internal_ip_1 = require("internal-ip");
const file_1 = require("../util/file");
const log_1 = require("../util/log");
// 服务对象
let server;
let uri;
/***
 * http文件下载服务,提供下载服务
 * @param options {port?:number}
 */
class HttpServer {
    constructor(port = 0) {
        this.port = port;
        this.start();
    }
    start() {
        return __awaiter(this, void 0, void 0, function* () {
            if (server) {
                log_1.default.verbose('当前服务已存在,不再重新新服务');
                return;
            }
            const app = express();
            app.use(bodyParser.json({ limit: '10000kb' }));
            app.use(bodyParser.urlencoded({ limit: '10000kb', extended: true }));
            app.get('/download', function (req, res) {
                let filePath = req.query.path;
                filePath = path.join(path.resolve('.'), filePath);
                if (fs.existsSync(filePath)) {
                    res.writeHead(200, {
                        // 告诉浏览器这是一个二进制文件
                        'Content-Type': 'application/octet-stream',
                        // 告诉浏览器这是一个需要下载的文件
                        'Content-Disposition': 'attachment; filename=' + encodeURI(file_1.fileName(filePath))
                    });
                    // 得到文件输入流
                    const readStream = fs.createReadStream(filePath);
                    readStream.on('data', (chunk) => {
                        // 文档内容以二进制的格式写到response的输出流
                        res.write(chunk, 'binary');
                    });
                    readStream.on('end', () => {
                        res.end();
                        log_1.default.verbose('下载完成', new Date());
                    });
                }
                else {
                    res.status(404).send('Sorry, 文件不存在!');
                }
            });
            server = app.listen(this.port, () => __awaiter(this, void 0, void 0, function* () {
                console.log('http Server started.');
                const host = yield internal_ip_1.default.v4();
                const port = server.address().port;
                uri = `http://${host}:${port}`;
                log_1.default.info('http Server started.', uri);
            }));
        });
    }
    /**
     * 返回端口
     */
    getPort() {
        return this.port;
    }
    /**
     * 获取下载服务地址
     */
    getUri() {
        log_1.default.verbose(uri);
        return `${uri}/download`;
    }
    getServer() {
        return server;
    }
}
exports.default = HttpServer;
