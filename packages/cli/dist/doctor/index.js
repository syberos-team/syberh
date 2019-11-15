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
const path = require("path");
const fs = require("fs-extra");
const _ = require("lodash/fp");
const targetSdkValidator_1 = require("./targetSdkValidator");
const syberhValidator_1 = require("./syberhValidator");
const sdkValidator_1 = require("./sdkValidator");
const log_1 = require("../util/log");
const constants_1 = require("../util/constants");
const chalk_1 = require("chalk");
const ora = require("ora");
const validators = {
    validators: [
        targetSdkValidator_1.default,
        syberhValidator_1.default,
        sdkValidator_1.default
    ]
};
// appPath
const appPath = process.cwd();
const NOTE_ALL_RIGHT = chalk_1.default.green('[✓] ');
const NOTE_VALID = chalk_1.default.yellow('[!] ');
const NOTE_INVALID = chalk_1.default.red('[✗] ');
const titleChalk = chalk_1.default.hex('#aaa');
const lineChalk = chalk_1.default.hex('#fff');
const solutionChalk = chalk_1.default.hex('#999');
// 返回是否有致命错误
function printReport(reports) {
    let hasError = false;
    _.forEach(report => {
        console.log('\n' + titleChalk(report.desc));
        if (report.raw) {
            console.log(report.raw);
            return;
        }
        if (_.getOr(0, 'lines.length', report) === 0) {
            console.log(`  ${NOTE_ALL_RIGHT}没有发现问题`);
            return;
        }
        _.forEach(line => {
            console.log('  ' +
                (line.valid ? NOTE_VALID : NOTE_INVALID) +
                lineChalk(line.desc));
            if (line.solution) {
                console.log('      ' + solutionChalk(line.solution));
            }
            hasError = (!line.valid);
        }, report.lines);
    }, reports);
    return hasError;
}
// 返回是否有致命错误
function diagnose({ checkGlobalTarget = false }) {
    return __awaiter(this, void 0, void 0, function* () {
        const PROJECT_CONF_PATH = path.join(process.cwd(), constants_1.PROJECT_CONFIG);
        log_1.log.verbose('PROJECT_CONF_PATH:', PROJECT_CONF_PATH);
        let projectConfig = {};
        // 检查全局target为false时，不判断projectConfig文件
        if (!checkGlobalTarget) {
            if (!fs.existsSync(PROJECT_CONF_PATH)) {
                console.log(chalk_1.default.red(`找不到项目配置文件${constants_1.PROJECT_CONFIG}，请确定当前目录是Syberh项目根目录!`));
                process.exit(1);
            }
            else {
                projectConfig = fs.readJSONSync(PROJECT_CONF_PATH);
            }
        }
        log_1.log.verbose('validators:', validators);
        const spinner = ora('正在诊断项目...').start();
        log_1.log.verbose('projectConfig', projectConfig);
        const reportsP = _.map(validator => validator({
            appPath,
            projectConfig,
            checkGlobalTarget,
            configPath: PROJECT_CONF_PATH
        }), validators.validators);
        const reports = yield Promise.all(reportsP);
        spinner.succeed('诊断完成');
        return printReport(reports);
    });
}
exports.default = diagnose;
