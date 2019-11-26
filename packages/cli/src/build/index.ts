import * as child_process from 'child_process'
import * as ip from 'internal-ip'
import * as os from 'os'
import { AppBuildConfig } from '../util/constants'
import Build from './build'
import { getProjectConfig, locateScripts } from '../syberos/helper'
import { log } from '../util/log';

/**
 * 编译APP
 * @param appPath 工程目录
 * @param param1 参数信息
 */
export async function build(appPath: string, webPath: string, config: AppBuildConfig) {
  log.verbose('build() start')
  const newConfig = { ...config, ...getProjectConfig(appPath) }
  const serverPort = 4399
  if (!newConfig.port) {
    Object.assign(newConfig, { port: serverPort })
  }
  if (!newConfig.serverIp) {
    let sip
    const ifaces = os.networkInterfaces()
    Object.keys(ifaces).forEach(function (dev) {
      ifaces[dev].forEach(function (details) {
        if (details.family === 'IPv4') {
          // 优先使用192.168.100.x段ip
          if (details.address.indexOf('192.168.100.10') >= 0) {
            sip = details.address
          }
        }
      })
    })

    if (!sip) {
      sip = await ip.v4()
    }
    Object.assign(newConfig, { serverIp: sip })
  }
  log.verbose('config:', JSON.stringify(newConfig))
  const { debug = false } = config

  const build = new Build(appPath, webPath, newConfig)
  if (newConfig.onlyBuildSop === true) {
    await build.buildSop(null)
  } else {
    await build.start(() => {
      // 启动devServer热更新服务
      if (debug) {
        const serverjs = locateScripts('devServer.js')
        child_process.fork(serverjs, [newConfig.port])
      }
    })
  }
}
