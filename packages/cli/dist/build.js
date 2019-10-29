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
const index_1 = require("./doctor/index");
const b = require("./build/index");
const helper_1 = require("./syberos/helper");
function build(appPath, webPath, buildConfig) {
    return __awaiter(this, void 0, void 0, function* () {
        if (buildConfig.type) {
            switch (buildConfig.type) {
                case "device" /* DEVICE */:
                    yield buildForDevice(appPath, webPath, buildConfig);
                    break;
                case "simulator" /* SIMULATOR */:
                    yield buildForSimulator(appPath, webPath, buildConfig);
                    break;
                default:
                    console.log(chalk_1.default.red('输入类型错误，目前只支持 device(真机)/simulator类型'));
            }
        }
        else {
            // 默认打SOP包
            yield buildSop(appPath, webPath, buildConfig);
        }
    });
}
exports.default = build;
function diagnoseFastfail(buildConfig) {
    return __awaiter(this, void 0, void 0, function* () {
        if (!buildConfig.nodoctor) {
            const hasFail = yield index_1.default();
            if (hasFail) {
                process.exit(0);
            }
        }
    });
}
function buildForDevice(appPath, webPath, buildConfig) {
    return __awaiter(this, void 0, void 0, function* () {
        const projectConfig = helper_1.getProjectConfig(appPath);
        yield diagnoseFastfail(buildConfig);
        yield b.build(appPath, webPath, {
            target: projectConfig.target,
            debug: buildConfig.debug,
            adapter: "device" /* DEVICE */
        });
    });
}
function buildForSimulator(appPath, webPathh, buildConfig) {
    return __awaiter(this, void 0, void 0, function* () {
        const projectConfig = helper_1.getProjectConfig(appPath);
        yield diagnoseFastfail(buildConfig);
        yield b.build(appPath, webPathh, {
            target: projectConfig.targetSimulator,
            debug: buildConfig.debug,
            adapter: "simulator" /* SIMULATOR */
        });
    });
}
function buildSop(appPath, webPathh, buildConfig) {
    return __awaiter(this, void 0, void 0, function* () {
        const projectConfig = helper_1.getProjectConfig(appPath);
        yield diagnoseFastfail(buildConfig);
        yield b.build(appPath, webPathh, {
            target: projectConfig.target,
            debug: buildConfig.debug,
            adapter: "device" /* DEVICE */,
            onlyBuildSop: true
        });
    });
}
