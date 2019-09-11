"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const dev_server_1 = require("@syberos/dev-server");
class DevServer {
    constructor(watchPath) {
        this.port = 4399;
        this.watchPath = watchPath;
        this.start();
    }
    start() {
        const server = new dev_server_1.default({ port: this.port });
        // tslint:disable-next-line: no-unused-expression
        new dev_server_1.Watcher(server, this.watchPath);
    }
}
exports.default = DevServer;
