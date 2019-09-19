import * as shelljs from 'shelljs'
import chalk from 'chalk'
import * as path from 'path'
import { log } from '../util/log'
import * as helper from '../syberos/helper'

interface ICdbSop {
  isSupportCdb(): boolean
  send(sopPath: string): void
  install(sopFilename: string): void
  startApp(): void
}

interface ISshSop {
  send(sopPath: string): void
  install(sopFilename: string): void
  startApp(): void
}

export class CdbSop implements ICdbSop {
  private pdkRootPath: string
  private targetName: string
  private sopid: string
  private projectName: string
  // cdb 设备名
  private cdbDevice: string

  constructor(pdkRootPath: string, targetName: string, sopid: string, projectName: string) {
    this.pdkRootPath = pdkRootPath
    this.targetName = targetName
    this.sopid = sopid
    this.projectName = projectName
  }

  isSupportCdb(): boolean {
    log.verbose('CdbSop isSupportCdb()')
    const cdbPath = this.locateCdb()
    log.verbose('%s devices', cdbPath)

    const cdbCmd = `${cdbPath} devices`
    log.verbose('执行：', cdbCmd)
    let result = shelljs.exec(`${cdbPath} devices`)
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

    const isSupportCdb = result.stdout.indexOf('-SyberOS') > 0
    if (isSupportCdb) {
      const lastIdx = result.stdout.indexOf('-SyberOS')
      const prefixSub = result.stdout.substring(0, lastIdx + 8)
      const firstIdx = prefixSub.lastIndexOf('\n')
      this.cdbDevice = result.stdout.substring(firstIdx + 1, lastIdx + 8)
    }
    log.verbose('isSupportCdb:%s, cdbDevice:%s', this.isSupportCdb, this.cdbDevice)
    return isSupportCdb
  }


  send(sopPath: string): void {
    log.verbose('CdbSop send(%s)', sopPath)
    const cdbPushCmd = `${this.locateCdb()} -s ${this.cdbDevice} push -p ${sopPath} /tmp`
    log.verbose('执行：', cdbPushCmd)
    shelljs.exec(cdbPushCmd)
  }

  install(sopFilename: string): void {
    log.verbose('CdbSop install(%s)', sopFilename)
    console.log(chalk.green('准备安装sop包'))
    log.verbose(sopFilename)
    const cmd = `expect ${helper.locateScripts('cdb-install-sop.sh')} ${this.locateCdb()} ${this.cdbDevice} ${sopFilename}`
    log.verbose('执行：', cmd)
    shelljs.exec(cmd)
  }

  startApp(): void {
    log.verbose('CdbSop startApp()')
    console.log(chalk.green('准备启动app'))
    log.verbose('%s:%s:uiapp', this.sopid, this.projectName)
    const cmd = `expect ${helper.locateScripts('cdb-start-app.sh')} ${this.locateCdb()} ${this.cdbDevice} ${this.sopid} ${this.projectName}`
    log.verbose('执行：', cmd)
    shelljs.exec(cmd)
  }

  /**
   * 查找cdb路径
   */
  private locateCdb(): string {
    log.verbose('Build locateCdb()')
    return path.join(
      this.pdkRootPath,
      'targets',
      this.targetName,
      'usr/lib/qt5/bin/cdb'
    )
  }
}

export class SshSop implements ISshSop {
  private ip: string
  private port: number
  private sopid: string
  private projectName: string

  constructor(ip: string, port: number, sopid: string, projectName: string) {
    this.ip = ip
    this.port = port
    this.sopid = sopid
    this.projectName = projectName
  }

  send(sopPath: string): void {
    log.verbose('SshSop send(%s)', sopPath)
    console.log(chalk.green('准备发送sop包'))
    log.verbose('ip:%s, port:%d, sopPath:%s', this.ip, this.port, sopPath)

    const cmd = `expect ${helper.locateScripts('scp-sop.sh')} ${this.ip} ${this.port} ${sopPath}`
    log.verbose('执行：', cmd)
    shelljs.exec(cmd)
  }

  install(sopFilename: string): void {
    log.verbose('SshSop install(%s)', sopFilename)
    console.log(chalk.green('准备安装sop包'))
    log.verbose(sopFilename)

    const nameSplit = sopFilename.split('-')

    const cmd = `expect ${helper.locateScripts('ssh-install-sop.sh')} ${this.ip} ${this.port} ${nameSplit[0]} ${sopFilename}`
    log.verbose('执行：', cmd)
    shelljs.exec(cmd)
  }

  startApp(): void {
    log.verbose('SshSop startApp()')
    console.log(chalk.green('准备启动app'))
    log.verbose('%s:%s:uiapp', this.sopid, this.projectName)

    const cmd = `expect ${helper.locateScripts('ssh-start-app.sh')} ${this.ip} ${this.port} ${this.sopid} ${this.projectName}`
    log.verbose('执行：', cmd)
    shelljs.exec(cmd)
  }


}