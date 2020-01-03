import * as path from 'path'
import * as fs from 'fs-extra'
import chalk from 'chalk'
import * as _ from 'lodash'
import * as inquirer from 'inquirer'
import * as semver from 'semver'
import Creator from './creator'
import { shouldUseYarn, shouldUseCnpm, getPkgVersion } from '../util'
import CONFIG from '../config'
import log from '../util/log'
import { qtversions } from '../syberos/configfile'

interface IProjectConf {
  projectName: string
  projectDir: string
  sopid: string
  storeBaseUrl: string
  template: 'default' | 'mobx' | 'redux'
  appName: string
  webPath: string
  typescript?: boolean
  css: 'none' | 'sass' | 'stylus' | 'less'
  date?: string
  src?: string
  // 是否创建demo项目
  example?: boolean
  targetName: string
}

export default class Project extends Creator {
  public rootPath: string
  public conf: IProjectConf

  constructor(options: IProjectConf) {
    super()
    const unSupportedVer = semver.lt(process.version, 'v7.6.0')
    if (unSupportedVer) {
      throw new Error('Node.js 版本过低，推荐升级 Node.js 至 v8.0.0+')
    }
    this.rootPath = this._rootPath

    this.conf = Object.assign(
      {
        typescript: false,
        projectName: '',
        projectDir: '',
        template: 'default',
        sopid: '',
        storeBaseUrl: CONFIG.STORE_BASE_URL,
        appName: '',
        webPath: CONFIG.SOURCE_DIR,
        example: false,
        targetName: ''
      },
      options
    )

    log.verbose('Project constructor() conf:', this.conf)
  }

  init() {
    console.log(chalk.green(`CLI 即将创建一个新项目!`))
    console.log(
      'Need help? Go and open issue: https://github.com/syberos-team/syberh'
    )
    console.log()
  }

  create() {
    this.ask().then(answers => {
      const date = new Date()
      // 对象
      const newAnswer = {}
      for (const obj in answers) {
        const value = _.trim(answers[obj])
        newAnswer[obj] = value
      }
      this.conf = Object.assign(this.conf, newAnswer)
      this.conf.date = `${date.getFullYear()}-${date.getMonth() +
        1}-${date.getDate()}`
      this.write()
    })
  }

  async ask() {
    const prompts: object[] = []
    const conf = this.conf

    const targetFullNames = await qtversions.getTargetNames()
    if (!targetFullNames || targetFullNames.length === 0) {
      console.log(chalk.red('未安装target，请先安装target'))
      process.exit(1)
    }
    const targetNames: string[] = []
    for (const targetName of targetFullNames) {
      const name = targetName.split('-')[2]
      if (!targetNames.includes(name)) {
        targetNames.push(name)
      }
    }

    log.verbose('targetNames: %j', targetNames)

    if (conf.example) {
      console.log(chalk.green(`正在创建示例项目!`))
      this.conf = Object.assign(this.conf, {
        projectName: 'example',
        appName: 'example',
        sopid: 'com.syberos.example'
      })
    }

    // tslint:disable-next-line: strict-type-predicates
    if (typeof conf.projectName !== 'string') {
      prompts.push({
        type: 'input',
        name: 'projectName',
        message: '请输入项目名称:',
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
    } else if (fs.existsSync(conf.projectName)) {
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

    if (!conf.appName) {
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

    if (!conf.sopid) {
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
    if (!conf.targetName) {
      prompts.push({
        type: 'list',
        name: 'targetName',
        message: '请选择target：',
        default: 'xuanwu',
        choices: targetNames
      })
    }
    return inquirer.prompt(prompts)
  }

  write(cb?: () => void) {
    const { template } = this.conf
    this.conf.src = CONFIG.SOURCE_DIR
    const { createApp } = require(path.join(
      this.templatePath(),
      template,
      'index.js'
    ))
    createApp(
      this,
      this.conf,
      {
        shouldUseYarn,
        shouldUseCnpm,
        getPkgVersion
      },
      cb
    )
  }
}
