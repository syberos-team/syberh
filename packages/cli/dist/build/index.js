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
const child_process = require("child_process");
const ip = require("internal-ip");
const os = require("os");
const build_1 = require("./build");
const helper_1 = require("../syberos/helper");
/**
 * 编译APP
 * @param appPath 工程目录
 * @param param1 参数信息
 */
function build(appPath, config) {
    return __awaiter(this, void 0, void 0, function* () {
        const newConfig = Object.assign({}, config, helper_1.getProjectConfig(appPath));
        const serverPort = 4399;
        if (!newConfig.port) {
            Object.assign(newConfig, { port: serverPort });
        }
        if (!newConfig.serverIp) {
            let sip;
            const ifaces = os.networkInterfaces();
            Object.keys(ifaces).forEach(function (dev) {
                ifaces[dev].forEach(function (details) {
                    if (details.family === 'IPv4') {
                        // 优先使用192.168.100.x段ip
                        if (details.address.indexOf('192.168.100.') >= 0) {
                            sip = details.address;
                        }
                    }
                });
            });
            if (!sip) {
                sip = yield ip.v4();
            }
            Object.assign(newConfig, { serverIp: sip });
        }
        const { debug = false } = config;
        if (debug) {
            const serverjs = helper_1.locateScripts('devServer.js');
            child_process.fork(serverjs);
        }
        const build = new build_1.default(appPath, newConfig);
        if (newConfig.onlyBuildSop === true) {
            build.buildSop();
        }
        else {
            build.start();
        }
    });
}
exports.build = build;
