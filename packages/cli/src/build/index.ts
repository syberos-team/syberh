import * as child_process from 'child_process'
import chalk from 'chalk'
import { BuildConfig } from './types'
import * as b from './build'
import { getProjectConfig, locateScripts, isTargetOS_5 } from '../syberos/helper'
import { log } from '../util/log';
import { DEVICES_TYPES } from '../util/constants'
import diagnose from '../doctor/index'
import { IProjectConfig } from '../util/types'
import CONFIG from '../config'



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
  if (!buildConfig.nodoctor) {
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
  const projectConf : IProjectConfig = getProjectConfig(appPath)
  // build命令参数
  const buildConfig : BuildConfig = { ...config }

  // 设置默认配置
  if(!projectConf.devServerIP){
    projectConf.devServerIP = CONFIG.DEV_SERVER_IP
  }
  if(!projectConf.devServerPort){
    projectConf.devServerPort = CONFIG.DEV_SERVER_PORT
  }

  console.log(chalk.green(`开始编译项目 ${chalk.bold(projectConf.projectName)}`))

  const build = new b.Build(appPath, projectConf, buildConfig)
  if (buildConfig.onlyBuild) {
    await build.start(null)
  } else {
    await build.start(() => {
      // 启动devServer热更新服务
      if (buildConfig.debug) {
        // TODO 5.0暂时关闭热更新服务
        if(isTargetOS_5(projectConf.target)){
          log.verbose('os5.0暂时关闭热更新服务')
          return;
        }
        const serverjs = locateScripts('devServer.js')
        child_process.fork(serverjs, [projectConf.devServerPort, projectConf.webPath])
      }
    })
  }
}
