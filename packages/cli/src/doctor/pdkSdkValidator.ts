import * as helper from '../syberos/helper'
import * as fs from 'fs-extra'
import * as shelljs from 'shelljs'
import * as path from 'path'
import { log } from '../util/log';
import { IErrorLine } from './interface'

async function buildReport(errors: IErrorLine[]) {
  return {
    desc: '检查SyberOS编译环境',
    lines: errors
  }
}



async function checkExpect(): Promise<IErrorLine[]> {
  log.verbose('checkExpect()')
  const errorLines: IErrorLine[] = []
  const cmd = 'whereis expect';
  const { stdout } = shelljs.exec(cmd)
  log.verbose('stdout:', stdout)
  if (stdout.indexOf('/usr/bin/expect') === -1) {
    log.warn('未找到expect :', stdout)
    errorLines.push({
      desc: `expect 未安装`,
      valid: false,
      solution: `请执行升级命令:  sudo apt-get install expect`
    })
  }

  return errorLines
}

async function checkSyberosPdk(): Promise<IErrorLine[]> {
  log.verbose('checkSyberosPdk() start')
  const pdkPath = await helper.locatePdk()
  const errorLines: IErrorLine[] = []

  if (!fs.pathExistsSync(pdkPath)) {
    errorLines.push({
      desc: '没有检查到Syberos-Pdk目录:' + pdkPath,
      valid: false,
      solution: '请重新安装sdk，并使用默认的安装路径，切勿修改sdk安装路径'
    })
    return errorLines
  }
  if (!fs.existsSync(path.join(pdkPath, 'sdk', 'sdk-root', 'syberos-sdk-chroot'))) {
    errorLines.push({
      desc: '无效的Syberos-Pdk目录:' + pdkPath,
      valid: false,
      solution: '请重新安装sdk，并使用默认的安装路径，切勿修改sdk安装路径'
    })
  }
  return errorLines
}

async function checkTarget(): Promise<IErrorLine[]> {
  log.verbose('checkTarget() start')
  const pdkPath = await helper.locatePdk()
  const errorLines: IErrorLine[] = []

  const targetPath = path.join(pdkPath, 'targets')
  if (!fs.pathExistsSync(targetPath)) {
    errorLines.push({
      desc: '没有检查到targets目录:' + targetPath,
      valid: false,
      solution: '请安装target，并使用默认的安装路径，切勿修改target安装路径'
    })
    return errorLines
  }
  const dirs = fs.readdirSync(targetPath)
  if (!dirs || dirs.length < 1 || !dirs.some((d) => { return d.startsWith('target-') })) {
    errorLines.push({
      desc: '未安装任何target',
      valid: false,
      solution: '请安装target，并使用默认的安装路径，切勿修改target安装路径'
    })
    return errorLines
  }
  return errorLines
}

async function checkSyberOSSDK(): Promise<IErrorLine[]> {
  log.verbose('checkSyberOSSDK() start')
  const sdkPath = helper.locateSdk()
  log.verbose('sdkPath() sdkPath', sdkPath)
  const errorLines: IErrorLine[] = []
  if (!fs.pathExistsSync(sdkPath)) {
    errorLines.push({
      desc: '没有检查到SyberOS-SDK目录:' + sdkPath,
      valid: false,
      solution: '请重新安装SyberOS SDK'
    })
    return errorLines
  }
  if (!fs.existsSync(path.join(sdkPath, 'ide', 'bin', 'qtcSyberIDE'))) {
    errorLines.push({
      desc: '无效的SyberOS-SDK目录:' + sdkPath,
      valid: false,
      solution: '请重新安装SyberOS SDK'
    })
  }
  return errorLines
}

export default async function () {
  const errorLines = await checkExpect();
  errorLines.push(... await checkSyberosPdk())
  errorLines.push(...await checkTarget())
  errorLines.push(...await checkSyberOSSDK())
  return buildReport(errorLines)
}
