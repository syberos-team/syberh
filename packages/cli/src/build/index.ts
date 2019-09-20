import * as child_process from 'child_process'
import * as ip from 'internal-ip'
import * as os from 'os'
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
    let sip
    const ifaces = os.networkInterfaces()
    Object.keys(ifaces).forEach(function (dev) {
      ifaces[dev].forEach(function (details) {
        if (details.family === 'IPv4') {
          // 优先使用192.168.100.x段ip
          if (details.address.indexOf('192.168.100.') >= 0) {
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
  const { debug = false } = config
  if (debug) {
    const serverjs = locateScripts('devServer.js')
    child_process.fork(serverjs)
  }
  const build = new Build(appPath, newConfig)
  if (newConfig.onlyBuildSop === true) {
    build.buildSop()
  } else {
    build.start()
  }
}
