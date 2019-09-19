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
const fs = require("fs-extra");
const chalk_1 = require("chalk");
const inquirer = require("inquirer");
const path = require("path");
const constants_1 = require("../util/constants");
const helper_1 = require("../syberos/helper");
const configfile_1 = require("../syberos/configfile");
/**
 * 重置设备的target
 * @param device
 */
exports.targetChoices = (device) => __awaiter(this, void 0, void 0, function* () {
    const targets = yield configfile_1.qtversions.getInstallTargets();
    const prompts = [];
    if (device === "simulator" /* SIMULATOR */) {
        // 如果为模拟器
        const targetChoices = targets.map((val) => {
            if (val.name.includes('i686')) {
                return val.name;
            }
            return '';
        }).filter((val) => { return val; });
        prompts.push({
            type: 'list',
            name: 'targetSimulator',
            message: '请选择target',
            choices: targetChoices
        });
    }
    if (device === "device" /* DEVICE */) {
        // 如果为真机
        const targetChoices = targets.map((val) => {
            if (val.name.includes('armv7tnhl')) {
                return val.name;
            }
            return '';
        }).filter((val) => { return val; });
        prompts.push({
            type: 'list',
            name: 'target',
            message: '请选择target',
            choices: targetChoices
        });
    }
    return inquirer.prompt(prompts);
});
/**
 * 检验并重置target
 * @param appPath app path
 * @param program 参数
 */
exports.targetReset = (appPath, program) => __awaiter(this, void 0, void 0, function* () {
    const { type, target } = program;
    try {
        // 校验是否需要重新设置target
        const projectConfig = helper_1.getProjectConfig(appPath);
        console.log('projectConf', JSON.stringify(projectConfig));
        // 是否需要重设target
        let reset = false;
        let targetName = target;
        // 检测是否有target
        if (target) {
            targetName = target;
            reset = true;
        }
        if (type && type === 'device' && !projectConfig.target) {
            targetName = 'device';
            reset = true;
        }
        if (type && type === 'simulator' && !projectConfig.targetSimulator) {
            targetName = 'simulator';
            reset = true;
        }
        if (reset) {
            const answers = yield exports.targetChoices(targetName);
            Object.assign(projectConfig, answers);
            // 格式化重写project.config.json
            fs.writeJSONSync(path.join(appPath, constants_1.PROJECT_CONFIG), projectConfig, {
                spaces: '\t',
                EOL: '\n'
            });
            console.log(chalk_1.default.green(`target重置完成,\n ${JSON.stringify(projectConfig, null, '\t')}`));
        }
        else {
            console.log(chalk_1.default.bgGreen('检验target完成'));
        }
        //   targetChoices(targetName).then(answers => {
        //     Object.assign(projectConfig, answers)
        //     // 格式化重写project.config.json
        //     fs.writeJSONSync(path.join(appPath, PROJECT_CONFIG), projectConfig, {
        //       spaces: '\t',
        //       EOL: '\n'
        //     })
        //     console.log(
        //       chalk.green(
        //         `target重置完成,\n ${JSON.stringify(projectConfig, null, '\t')}`
        //       )
        //     )
        //   })
        // } else {
        //   console.log(chalk.bgGreen('检验target完成'))
        // }
    }
    catch (e) {
        console.error('e', e);
        throw new Error(`请检查配置文件${constants_1.PROJECT_CONFIG}格式，目前非JSON格式`);
    }
});
