import * as inquirer from 'inquirer'
import * as _ from 'lodash'
import * as os from 'os'
import * as fs from 'fs-extra'
import { Install, InstallOption } from './install'

function ask() {
  const home = os.homedir()
  const prompts: object[] = []
  prompts.push({
    type: 'list',
    name: 'installType',
    message: '选择安装的类型：',
    choices: [
      'sdk',
      'target'
    ]
  })
  prompts.push({
    type: 'input',
    name: 'installPath',
    message: '安装的路径：',
    default: home + '/Syberos-Pdk',
    validate: val => {
      if (!val) {
        return '请输入安装的路径';
      }
      return true;
    }
  })
  prompts.push({
    type: 'input',
    name: 'sdkPath',
    message: 'sdk安装包的路径：',
    validate: val => {
      if (!val) {
        return '请输入sdk安装包的路径';
      }
      if (!fs.existsSync(val)) {
        return 'sdk安装包的路径无效'
      }
      return true;
    },
    when: answers => {
      return answers.installType === 'sdk'
    }
  })
  prompts.push({
    type: 'input',
    name: 'targetPath',
    message: 'target安装包的路径：',
    validate: val => {
      if (!val) {
        return '请输入target安装包的路径';
      }
      if (!fs.existsSync(val)) {
        return 'target安装包的路径无效'
      }
      return true;
    },
    when: answers => {
      return answers.installType === 'target'
    }
  })
  prompts.push({
    type: 'password',
    name: 'password',
    message: '当前用户密码：',
    validate: val => {
      if (!val) {
        return '请输入当前用户密码';
      }
      return true;
    }
  })
  return inquirer.prompt(prompts)
}

export default function install(): void {
  ask().then(answers => {
    const option: InstallOption = {
      password: answers['password'],
      installType: Install.installType(answers['installType']),
      sdkPath: answers['sdkPath'],
      targetPath: answers['targetPath'],
      installPath: answers['installPath']
    }

    new Install(option).exec()
  })
}