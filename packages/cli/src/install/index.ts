import * as inquirer from 'inquirer'
import * as _ from 'lodash'
import * as os from 'os'
import * as fs from 'fs-extra'
import * as path from 'path'
import chalk from 'chalk'
import { Install, InstallOption } from './install'
import { qtversions } from '../syberos/configfile'
import * as helper from './helper'

function sdkAsk(): object[] {
  const prompts: object[] = []
  prompts.push({
    type: 'input',
    name: 'installPath',
    message: '安装的路径：',
    default: () => {
      return os.homedir() + '/Syberos-Pdk'
    },
    validate: val => {
      if (!val) {
        return '请输入安装的路径';
      }
      return true;
    },
    when: answers => {
      return answers.installType === 'sdk'
    }
  })
  prompts.push({
    type: 'input',
    name: 'sdkPath',
    message: 'sdk安装包的路径：',
    default: helper.sdkPackagePath(),
    validate: val => {
      if (!val) {
        return '请输入sdk安装包的路径';
      }
      if (!fs.existsSync(val)) {
        return 'sdk安装包的路径无效，未找到安装包'
      }
      if (!fs.lstatSync(val).isFile()) {
        return 'sdk安装包的路径无效，无效的安装包'
      }
      return true;
    },
    when: answers => {
      return answers.installType === 'sdk'
    }
  })
  return prompts
}

function targetAsk(): object[] {
  const prompts: object[] = []
  prompts.push({
    type: 'input',
    name: 'installPath',
    message: '已安装的sdk路径：',
    default: async () => {
      const sdkInstallPath = await qtversions.getSdkInstallPath()
      if (!sdkInstallPath) {
        console.log(chalk.red('>>'), chalk.yellow('检测到尚未安装sdk，请先安装sdk'))
        process.exit(1)
      }
      return sdkInstallPath
    },
    validate: val => {
      if (!val) {
        return '请输入sdk安装包的路径';
      }
      if (!fs.existsSync(val)) {
        return 'sdk路径无效'
      }
      const chrootPath = path.join(val, 'sdk/sdk-root/syberos-sdk-chroot')
      if (!fs.existsSync(chrootPath)) {
        return '无效的sdk'
      }
      return true;
    },
    when: answers => {
      return answers.installType === 'target'
    }
  })

  const targetPathvalidator = (val: any) => {
    if (!val) {
      return '请输入target安装包的路径';
    }
    if (!fs.existsSync(val)) {
      return 'target安装包的路径无效，安装包不存在'
    }
    if (!fs.lstatSync(val).isFile()) {
      return 'target安装包的路径无效，路径不是有效的安装包'
    }
    return true;
  }

  const targetPaths = helper.targetPackagePaths()
  if (targetPaths && targetPaths.length > 0) {
    prompts.push({
      type: 'list',
      name: 'targetPath',
      message: 'target安装包的路径：',
      choices: targetPaths,
      validate: targetPathvalidator,
      when: answers => {
        return answers.installType === 'target'
      }
    })
  } else {
    prompts.push({
      type: 'input',
      name: 'targetPath',
      message: 'target安装包的路径：',
      validate: targetPathvalidator,
      when: answers => {
        return answers.installType === 'target'
      }
    })
  }
  return prompts
}

function cceAsk(): object[] {
  const prompts: object[] = []
  prompts.push({
    type: 'input',
    name: 'installCCEPath',
    message: 'cce安装路径：',
    default: () => {
      return os.homedir()
    },
    validate: val => {
      if (!val) {
        return '请输入安装的路径';
      }
      return true;
    },
    when: answers => {
      return answers.installType === 'cce'
    }
  })
  prompts.push({
    type: 'input',
    name: 'ccePath',
    message: 'cce安装包的路径：',
    default: helper.sdkPackagePath(),
    validate: val => {
      if (!val) {
        return '请输入cce安装包的路径';
      }
      if (!fs.existsSync(val)) {
        return 'cce安装包的路径无效，未找到安装包'
      }
      if (!fs.lstatSync(val).isFile()) {
        return 'cce安装包的路径无效，无效的安装包'
      }
      return true;
    },
    when: answers => {
      return answers.installType === 'cce'
    }
  })
  return prompts
}

function ask() {
  let prompts: object[] = []
  prompts.push({
    type: 'list',
    name: 'installType',
    message: '选择安装的类型：',
    choices: [
      'sdk',
      'target',
      'cce'
    ]
  })
  prompts = prompts.concat(sdkAsk()).concat(targetAsk().concat(cceAsk()))

  prompts.push({
    type: 'password',
    name: 'password',
    message: '当前用户密码：',
    validate: val => {
      if (!val) {
        return '请输入当前用户密码';
      }
      return true;
    },
    when: answers => {
      return answers.installType !== 'cce'
    }
  })
  return inquirer.prompt(prompts)
}

export default function install(): void {
  ask().then(answers => {
    console.log(JSON.stringify(answers))
    const option: InstallOption = {
      password: answers['password'],
      installType: Install.installType(answers['installType']),
      sdkPath: answers['sdkPath'],
      targetPath: answers['targetPath'],
      ccePath: answers['ccePath'],
      installPath: answers['installPath'],
      installCCEPath: answers['installCCEPath']
    }

    new Install(option).exec()
  })
}