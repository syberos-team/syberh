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
function build(appPath, buildConfig) {
<<<<<<< HEAD
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
=======
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
            yield buildSop(appPath, buildConfig);
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
function buildForDevice(appPath, buildConfig) {
    return __awaiter(this, void 0, void 0, function* () {
        const projectConfig = helper_1.getProjectConfig(appPath);
        yield diagnoseFastfail(buildConfig);
        yield b.build(appPath, {
            target: projectConfig.target,
            debug: buildConfig.debug,
            adapter: "device" /* DEVICE */
        });
    });
}
function buildForSimulator(appPath, buildConfig) {
    return __awaiter(this, void 0, void 0, function* () {
        const projectConfig = helper_1.getProjectConfig(appPath);
        yield diagnoseFastfail(buildConfig);
        yield b.build(appPath, {
            target: projectConfig.targetSimulator,
            debug: buildConfig.debug,
            adapter: "simulator" /* SIMULATOR */
        });
    });
}
function buildSop(appPath, buildConfig) {
    return __awaiter(this, void 0, void 0, function* () {
        const projectConfig = helper_1.getProjectConfig(appPath);
        yield diagnoseFastfail(buildConfig);
        yield b.build(appPath, {
            target: projectConfig.target,
            debug: buildConfig.debug,
            adapter: "device" /* DEVICE */,
            onlyBuildSop: true
        });
    });
>>>>>>> upstream/v1.1.1
}
