import { log } from '../util/log'
import * as shelljs from 'shelljs'
import chalk from 'chalk'
import * as os from 'os'
import * as path from 'path'

const IP_CHECK = '192.168.100.'

export class ConnectChecker {
  private pdkRootPath: string
  private targetName: string

  constructor(pdkRootPath: string, targetName: string) {
    this.pdkRootPath = pdkRootPath
    this.targetName = targetName
  }

  isCdbEnabled(): boolean {
    log.verbose('ConnectChecker isCdbEnabled()')
    const result = this.execCdbDevices()
    return result.indexOf('-SyberOS') > 0
  }

  isSshEnabled(): boolean {
    log.verbose('ConnectChecker isSshEnabled()')
    const interfaces = os.networkInterfaces()
    log.verbose('检查本机IP：%j', interfaces)
    for (const devName in interfaces) {
      for (const ipAddr of interfaces[devName]) {
        if (ipAddr.address && ipAddr.address.startsWith(IP_CHECK)) {
          log.verbose('IP：%j', ipAddr);
          return true
        } else if (ipAddr.mac === '00:22:33:44:55:66') {
          console.log(chalk.yellow('当前连接的设备可能需要手动配置ip，请配置ip后再次尝试'))
        }
      }
    }
    return false
  }


  findCdbDevice(): string | null {
    const result = this.execCdbDevices()
    const isSupportCdb = result.indexOf('-SyberOS') > 0
    if (isSupportCdb) {
      const lastIdx = result.indexOf('-SyberOS')
      const prefixSub = result.substring(0, lastIdx + 8)
      const firstIdx = prefixSub.lastIndexOf('\n')
      return result.substring(firstIdx + 1, lastIdx + 8)
    }
    return null
  }

  private execCdbDevices(): string {
    log.verbose('ConnectChecker isCdbEnabled()')
    const cdbPath = this.locateCdb()
    log.verbose('%s devices', cdbPath)

    const cdbCmd = `${cdbPath} devices`
    log.verbose('执行：', cdbCmd)
    // 关闭控制台输出命令执行结果
    shelljs.config.silent = true
    let result = shelljs.exec(`${cdbPath} devices`)
    // 执行完成后重新打开
    shelljs.config.silent = false
    log.verbose('执行结果：', result)

    // 出现no permissions时，需要重启cdb服务
    if (result.stdout.indexOf('no permissions') > 0) {
      console.log(chalk.yellow('正在重启cdb服务，启动过程中可能需要输入当前用户的密码...'))

      let cmd = `${cdbPath} kill-server`
      log.verbose('执行：', cmd)
      shelljs.exec(cmd)

      cmd = `sudo ${cdbPath} start-server`
      log.verbose('执行：', cmd)
      shelljs.exec(cmd)

      cmd = `${cdbPath} devices`
      log.verbose('执行：', cmd)
      result = shelljs.exec(cmd)
    }
    return result.stdout || ''
  }


  /**
   * 查找cdb路径
   */
  private locateCdb(): string {
    log.verbose('ConnectChecker locateCdb()')
    return path.join(
      this.pdkRootPath,
      'targets',
      this.targetName,
      'usr/lib/qt5/bin/cdb'
    )
  }

}
