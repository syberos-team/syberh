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
const chalk_1 = require("chalk");
function build(appPath, buildConfig) {
    return __awaiter(this, void 0, void 0, function* () {
        if (buildConfig.type) {
            switch (buildConfig.type) {
                case "device" /* DEVICE */:
                    yield buildForDevice(appPath, buildConfig);
                    break;
                case "simulator" /* SIMULATOR */:
                    yield buildForSimulator(appPath, buildConfig);
                    break;
                default:
                    console.log(chalk_1.default.red('输入类型错误，目前只支持 device(真机)/simulator类型'));
            }
        }
        else {
            // 默认打SOP包
            buildSop(appPath, buildConfig);
        }
    });
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
