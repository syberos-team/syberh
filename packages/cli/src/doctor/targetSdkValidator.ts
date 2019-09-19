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
      solution: `请执行安装命令: sudo apt-get install expect`
    })
  }

  return errorLines
}

async function checkSyberosSdk(): Promise<IErrorLine[]> {
  log.verbose('checkSyberosSdk() start')
  const sdkRootPath = await helper.locateSdk()
  const errorLines: IErrorLine[] = []

  if (!fs.pathExistsSync(sdkRootPath)) {
    errorLines.push({
      desc: '未安装SyberOS sdk',
      valid: false,
      solution: '请安装SyberOS sdk'
    })
    return errorLines
  }
  if (!fs.existsSync(path.join(sdkRootPath, 'sdk/sdk-root/syberos-sdk-chroot'))) {
    errorLines.push({
      desc: '无效的SyberOS sdk',
      valid: false,
      solution: '请重新安装'
    })
  }
  return errorLines
}

async function checkTarget(projectConfig: any): Promise<IErrorLine[]> {
  log.verbose('targetSdkValidator checkTarget(%j)', projectConfig)
  const targetPaths = await helper.locateAllTarget()
  const errorLines: IErrorLine[] = []

  if (!projectConfig.target) {
    errorLines.push({
      desc: 'target配置缺失',
      valid: false,
      solution: '请检查 project.config.json'
    })
    return errorLines
  }
  if (!projectConfig.targetSimulator) {
    errorLines.push({
      desc: 'targetSimulator配置缺失',
      valid: true,
      solution: '将无法在模拟器中运行，请检查 project.config.json'
    })
  }

  if (!targetPaths || targetPaths.length < 1) {
    errorLines.push({
      desc: '未安装任何target',
      valid: false,
      solution: '请安装target'
    })
    return errorLines
  }

  const checkPathExists = (targetPath: string): IErrorLine | null => {
    if (!fs.pathExistsSync(targetPath)) {
      return {
        desc: '检测到没有正确安装target',
        valid: false,
        solution: '请重新安装target'
      }
    }
    return null
  }

  let hasTarget = false
  let hasTargetSimulator = false
  for (const targetPath of targetPaths) {
    if (targetPath.includes(`/${projectConfig.target}/`)) {
      const errline = checkPathExists(targetPath)
      if (errline) {
        errorLines.push(errline)
        return errorLines
      } else {
        hasTarget = true
      }
    }
    if (projectConfig.targetSimulator) {
      if (targetPath.includes(`/${projectConfig.targetSimulator}/`)) {
        const errline = checkPathExists(targetPath)
        if (errline) {
          errorLines.push(errline)
          return errorLines
        } else {
          hasTargetSimulator = true
        }
      }
    } else {
      // 无需检查 targetSimulator
      hasTargetSimulator = true
    }
  }
  if (!hasTarget) {
    errorLines.push({
      desc: 'target未安装',
      valid: false,
      solution: '请安装target: ' + projectConfig.target
    })
    return errorLines
  }
  if (!hasTargetSimulator) {
    errorLines.push({
      desc: 'target未安装',
      valid: false,
      solution: '请安装target: ' + projectConfig.targetSimulator
    })
    return errorLines
  }
  return errorLines
}


export default async function (params) {
  log.verbose('targetSdkValidator: ', params)

  const errorLines = await checkExpect();
  errorLines.push(... await checkSyberosSdk())
  errorLines.push(...await checkTarget(params['projectConfig']))

  return buildReport(errorLines)
}
