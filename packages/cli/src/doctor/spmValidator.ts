import { log } from '../util/log'
import { IErrorLine } from './interface'
import * as shelljs from 'shelljs'

async function buildReport(errors: IErrorLine[]) {
  return {
    desc: '检查 spm',
    lines: errors
  }
}

async function checkSpm(): Promise<IErrorLine[]> {
  log.verbose('checkSpm()')
  const errorLines: IErrorLine[] = []
  const cmd = 'which spm';
  shelljs.config.silent = true
  const { stdout } = shelljs.exec(cmd)
  shelljs.config.silent = false

  log.verbose('cmd: %s, stdout: %s', cmd, stdout)
  if (!stdout.endsWith('/spm')) {
    log.warn('未找到spm: ', stdout)
    errorLines.push({
      desc: 'spm 未安装',
      valid: false,
      solution: '请执行安装命令: curl -o spm https://spm.syberos.com/download?version=latest && sudo install -m 755 ./spm /usr/local/bin'
    })
  }

  return errorLines
}

export default async function (params) {
  log.verbose('spmValidator: ', params)

  const errorLines = await checkSpm();
  return buildReport(errorLines)
}