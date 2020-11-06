import * as child_process from 'child_process'
import chalk from 'chalk'
import { BuildConfig } from './types'
import * as b from './build'
import * as helper from '../syberos/helper'
import { log } from '../util/log';
import { DEVICES_TYPES } from '../util/constants'
import diagnose from '../doctor/index'
import { IProjectConfig, DEFAULT_PROJECT_CONFIG } from '../util/types'
import * as inquirer from 'inquirer'
import * as ora from 'ora'


/**
 * build命令入口
 * @param appPath 应用路径
 * @param buildConfig build命令参数
 */
export default async function build(appPath: string, buildConfig: BuildConfig) {
  if(buildConfig.type !== DEVICES_TYPES.DEVICE && buildConfig.type !== DEVICES_TYPES.SIMULATOR){
    console.log(
      chalk.red('输入类型错误，目前只支持 device(真机)/simulator类型')
    )
    return;
  }
  await diagnoseFastfail(buildConfig)
  await executeBuild(appPath, buildConfig)
}

async function diagnoseFastfail(buildConfig: BuildConfig) {
  if (buildConfig.doctor) {
    const hasFail = await diagnose({ checkGlobalTarget: false })
    if (hasFail) {
      process.exit(0)
    }
  }
}

/**
 * 编译APP
 * @param appPath 工程目录
 * @param param1 参数信息
 */
async function executeBuild(appPath: string, config: BuildConfig) {
  log.verbose('build() start')
  // 获取project.config.json
  let projectConf : IProjectConfig = helper.getProjectConfig(appPath)
  // 设置默认值
  projectConf = Object.assign(DEFAULT_PROJECT_CONFIG, projectConf)

  // build命令参数
  const buildConfig : BuildConfig = { ...config }

  // os5.0时不校验用户密码
  if(helper.isTargetOS_5(projectConf.target)){
    // 开始构建
    buildApp(appPath, projectConf, buildConfig)
    return
  }

  // 问询
  const answers = await ask()
  const userPassword = answers['password']

  const spinner = ora('校验用户密码...').start()
  helper.checkSudoPasswordAsync(userPassword).then((success:boolean) => {
    if(success){
      buildConfig.buildAsk = {
        password: userPassword
      }
      spinner.succeed('密码校验通过')
      // 开始构建
      buildApp(appPath, projectConf, buildConfig)
    }else{
      spinner.fail('密码校验失败，终止编译')
      process.exit(1)
    }
  })
}


// 开始构建应用
async function buildApp(appPath: string, projectConf : IProjectConfig, buildConfig : BuildConfig){
  console.log(chalk.green(`开始编译项目 ${chalk.bold(projectConf.projectName)}`))

  const build = new b.Build(appPath, projectConf, buildConfig)
  if (buildConfig.onlyBuild) {
    await build.start(null)
  } else {
    await build.start(() => {
      // 开启热更新，启动devServer热更新服务
      if (buildConfig.hot) {
        // TODO 5.0暂时关闭热更新服务
        if(helper.isTargetOS_5(projectConf.target)){
          log.verbose('os5.0暂时关闭热更新服务')
          return;
        }
        const serverjs = helper.locateScripts('devServer.js')
        child_process.fork(serverjs, [projectConf.devServerPort, projectConf.webPath])
      }
    })
  }
}

// 询问密码
async function ask() : Promise<inquirer.PromptModule> {
  const prompts: object[] = []
  prompts.push({
    type: 'password',
    name: 'password',
    message: '请输入当前用户密码:',
    validate(input:any) {
      if (!input) {
        return '必须输入当前用户密码！'
      }
      return true
    }
  })
  return inquirer.prompt(prompts)
}

