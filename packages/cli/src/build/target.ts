import * as fs from 'fs-extra'
import chalk from 'chalk'
import * as inquirer from 'inquirer'
import * as path from 'path'
import {
  TARGET_NAMES,
  DEVICES_TYPES,
  TARGET_SIMULATOR_NAMES,
  PROJECT_CONFIG
} from '../util/constants'
import { getProjectConfig } from '../syberos/helper'

/**
 * 重置设备的target
 * @param device
 */
export const targetChoices = (device: DEVICES_TYPES) => {
  const prompts: object[] = []
  if (device === DEVICES_TYPES.SIMULATOR) {
    // 如果为模拟器
    const targetChoices: object[] = []
    for (const dd in TARGET_SIMULATOR_NAMES) {
      targetChoices.push({
        name: dd,
        value: TARGET_SIMULATOR_NAMES[dd]
      })
    }
    prompts.push({
      type: 'list',
      name: 'targetSimulator',
      message: '请选择target',
      choices: targetChoices
    })
  }

  if (device === DEVICES_TYPES.DEVICE) {
    // 如果为模拟器
    const targetChoices: object[] = []
    for (const dd in TARGET_NAMES) {
      targetChoices.push({
        name: dd,
        value: TARGET_NAMES[dd]
      })
    }
    prompts.push({
      type: 'list',
      name: 'target',
      message: '请选择target',
      choices: targetChoices
    })
  }

  return inquirer.prompt(prompts)
}

/**
 * 检验并重置target
 * @param appPath app path
 * @param program 参数
 */
export const targetReset = (appPath: string, program: any) => {
  const { type, target } = program
  try {
    // 校验是否需要重新设置target
    const projectConfig = getProjectConfig(appPath)
    console.log('projectConf', JSON.stringify(projectConfig))
    // 是否需要重设target
    let reset = false
    let targetName = target
    // 检测是否有target
    if (target) {
      targetName = target
      reset = true
    }
    if (type && type === 'device' && !projectConfig.target) {
      targetName = 'device'
      reset = true
    }
    if (type && type === 'simulator' && !projectConfig.targetSimulator) {
      targetName = 'simulator'
      reset = true
    }
    if (reset) {
      targetChoices(targetName).then(answers => {
        Object.assign(projectConfig, answers)
        // 格式化重写project.config.json
        fs.writeJSONSync(path.join(appPath, PROJECT_CONFIG), projectConfig, {
          spaces: '\t',
          EOL: '\n'
        })

        console.log(
          chalk.green(
            `target重置完成,\n ${JSON.stringify(projectConfig, null, '\t')}`
          )
        )
      })
    } else {
      console.log(chalk.bgGreen('检验target完成'))
    }
  } catch (e) {
    console.error('e', e)
    throw new Error(`请检查配置文件${PROJECT_CONFIG}格式，目前非JSON格式`)
  }
}
