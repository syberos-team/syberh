"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const chalk_1 = require("chalk");
function build(appPath, buildConfig) {
    const { type, debug, port } = buildConfig;
    if (type) {
        switch (type) {
            case "device" /* DEVICE */:
                buildForDevice(appPath, { debug, port });
                break;
            case "simulator" /* SIMULATOR */:
                buildForSimulator(appPath, { debug, port });
                break;
            default:
                console.log(chalk_1.default.red('输入类型错误，目前只支持 device(真机)/simulator类型'));
        }
    }
    else {
        // 默认打SOP包
        buildSop(appPath, { debug, port });
    }
}
exports.default = build;
function buildForDevice(appPath, buildConfig) {
    require('./build/index').build(appPath, Object.assign({}, buildConfig, { adapter: "device" /* DEVICE */ }));
}
function buildForSimulator(appPath, buildConfig) {
    require('./build/index').build(appPath, Object.assign({}, buildConfig, { adapter: "simulator" /* SIMULATOR */ }));
}
function buildSop(appPath, buildConfig) {
    require('./build/index').build(appPath, Object.assign({}, buildConfig, { onlyBuildSop: true }));
}
