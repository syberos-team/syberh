import * as shelljs from 'shelljs'
import chalk from 'chalk'
import * as path from 'path'
import { log } from '../util/log'
import * as helper from '../syberos/helper'
import * as connect from './connect'

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

    const checker = new connect.ConnectChecker(this.pdkRootPath, this.targetName)
    const cdbDevice = checker.findCdbDevice()
    if (cdbDevice) {
      this.cdbDevice = cdbDevice
    }
    log.verbose('isSupportCdb:%s, cdbDevice:%s', this.isSupportCdb, this.cdbDevice)
    return !!cdbDevice
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