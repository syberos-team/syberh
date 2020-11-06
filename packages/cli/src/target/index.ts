import { findTargets } from '../syberos/helper'
import chalk from 'chalk'
import * as fs from 'fs-extra'
import * as inquirer from 'inquirer'
import { TargetType, ITargetOption, IAnswer } from './types'
import { IProjectConfig } from '../util/types'



export const resetTarget = (option: ITargetOption) => {

    ask(option).then((answers:any) => {
        if(!answers){
            return
        }
        const result: IAnswer = {
            target: answers['target'],
            targetSimulator: answers['targetSimulator']
        }
        updateProjectConfig(option, result)
        console.log(chalk.green('target 重置成功'))
    })
}


async function ask(option: ITargetOption): Promise<inquirer.PromptModule | null> {
    const targetNames = await findTargets()
    if(!targetNames || targetNames.length === 0){
        console.log(chalk.red('未安装target，请先安装target'))
        return null
    }
    const prompts: object[] = []

    if(option.type === TargetType.ALL || option.type === TargetType.DEVICE) {
        prompts.push({
          type: 'list',
          name: 'target',
          message: '请选择真机target：',
          choices: targetNames
        })
    }
    if(option.type === TargetType.ALL || option.type === TargetType.SIMULATOR) {
        prompts.push({
            type: 'list',
            name: 'targetSimulator',
            message: '请选择模拟器target：',
            choices: targetNames
        })
    }
    return inquirer.prompt(prompts)
}

function updateProjectConfig(option: ITargetOption, answer: IAnswer){
    const projectConfig: IProjectConfig = fs.readJSONSync(option.projectConfigPath)
    if(answer.target){
        projectConfig.target = answer.target
    }
    if(answer.targetSimulator){
        projectConfig.targetSimulator = answer.targetSimulator
    }
    fs.writeJSONSync(option.projectConfigPath, projectConfig, {
        encoding: 'utf-8',
        spaces: '\t',
        EOL: '\n'
    })
}
