import * as fs from 'fs-extra'
import chalk from 'chalk'
import * as _ from 'lodash'
import * as inquirer from 'inquirer'
import * as semver from 'semver'
import Creator from './creator'
import log from '../util/log'
import { findTargets } from '../syberos/helper'
import { DEFAULT_PROJECT_CONFIG } from '../util/types'
import { ICreateProjectOption, IProjectTemplate } from './types'
import { createApp } from './template'



export default class Project extends Creator {
  private option: ICreateProjectOption
  private projectConfig: IProjectTemplate

  constructor(option: ICreateProjectOption) {
    super()
    const unSupportedVer = semver.lt(process.version, 'v7.6.0')
    if (unSupportedVer) {
      throw new Error('Node.js 版本过低，推荐升级 Node.js 至 v8.0.0+')
    }
    this.option = option
    this.projectConfig = {
      ...DEFAULT_PROJECT_CONFIG
    }
    this.projectConfig.projectName = option.projectName || ''

    log.verbose('Project constructor() conf:', this.projectConfig)
  }

  init() {
    console.log(chalk.green(`CLI 即将创建一个新项目!`))
    console.log(
      'Need help? Go and open issue: https://github.com/syberos-team/syberh'
    )
    console.log()
  }

  create() {
    this.ask().then((answers:any) => {
      // 对象
      const newAnswer = {}
      for (const obj in answers) {
        const value = _.trim(answers[obj])
        newAnswer[obj] = value
      }
      this.projectConfig = Object.assign(this.projectConfig, newAnswer)

      this.write()
    })
  }

  async ask() {
    const prompts: object[] = []

    const targetNames = await findTargets()
    log.verbose('targetNames: %j', targetNames)
    if(!targetNames || targetNames.length === 0){
      console.log(chalk.yellow('未检测到已安装的target，请先安装target'))
      process.exit(1)
    }

    if (this.option.example) {
      console.log(chalk.green(`正在创建示例项目!`))
      this.projectConfig = Object.assign(this.projectConfig, {
        projectName: 'example',
        appName: 'example',
        sopid: 'com.syberos.example'
      })
    }

    if (!this.projectConfig.projectName) {
      prompts.push({
        type: 'input',
        name: 'projectName',
        message: '请输入项目名称(应用id):',
        validate(input) {
          if (!input) {
            return '项目名不能为空！'
          }
          if (fs.existsSync(input)) {
            return '当前目录已经存在同名项目，请换一个项目名！'
          }
          return true
        }
      })
    } else if (fs.existsSync(this.projectConfig.projectName)) {
      prompts.push({
        type: 'input',
        name: 'projectName',
        message: '当前目录已经存在同名项目，请换一个项目名！',
        validate(input) {
          if (!input) {
            return '项目名不能为空！'
          }
          if (fs.existsSync(input)) {
            return '项目名依然重复！'
          }
          return true
        }
      })
    }

    if (!this.projectConfig.appName) {
      prompts.push({
        type: 'input',
        name: 'appName',
        message: '请输入应用名称:',
        validate(input) {
          if (!input) {
            return '应用名称不能为空！'
          }
          return true
        }
      })
    }

    if (!this.projectConfig.sopid) {
      prompts.push({
        type: 'input',
        name: 'sopid',
        message: '请输入sopid,如【com.syberh.myapp】:',
        validate(input) {
          if (!input) {
            return 'sopid不能为空！'
          }
          const re = /[\u4E00-\u9FA5]|[\uFE30-\uFFA0]/gi
          if (re.test(input)) {
            return 'sopid不能含有中文！'
          }

          return true
        }
      })
    }
    if (!this.projectConfig.target) {
      prompts.push({
        type: 'list',
        name: 'target',
        message: '请选择target：',
        choices: targetNames
      })
    }
    return inquirer.prompt(prompts)
  }

  write(cb?: Function) {
    createApp(
      this,
      this.option,
      this.projectConfig,
      cb
    )
  }

}
