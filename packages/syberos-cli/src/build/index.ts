import * as child_process from 'child_process'
import * as ip from 'internal-ip';
import { AppBuildConfig } from '../util/constants'
import Build from './build'
import { getProjectConfig, locateScripts } from '../syberos/helper'

/**
 * 编译APP
 * @param appPath 工程目录
 * @param param1 参数信息
 */
export async function build(appPath: string, config: AppBuildConfig) {
  const newConfig = { ...config, ...getProjectConfig(appPath) }
  const serverPort = 4399
  if (!newConfig.port) {
    Object.assign(newConfig, { port: serverPort })
  }

  if (!newConfig.serverIp) {
    const ipv4 = await ip.v4()
    Object.assign(newConfig, { serverIp: ipv4 })
  }
  const { debug = false } = config
  if (debug) {
    const serverjs = locateScripts('devServer.js');
    child_process.fork(serverjs)
  }
  const build = new Build(appPath, newConfig)
  if (newConfig.onlyBuildSop === true) {
    build.buildSop()
  } else {
    build.start()
  }

}
