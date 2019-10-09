import * as _ from 'lodash/fp'
import * as shelljs from 'shelljs';
import log from '../util/log'
import latestVersion from '../syberos/latestVersion'


// 检查的包的名称
const pkgName = '@syberos/cli';
/**
 * 检查syberh是否需要升级
 */
async function checkSyberhPkg() {

  log.verbose('checkSyberhPkg () start')
  let errorLines: any[] = []

  let remoteVersion
  try {
    remoteVersion = await latestVersion(pkgName, 5000)
    log.verbose('remoteVersion:', remoteVersion)
  } catch (e) {
    log.verbose('检查@syberos/cli版本失败', e)
    return {
      desc: '检查@syberos/cli版本',
      lines: [{
        desc: '连接超时',
        valid: true,
        solution: '请检查网络'
      }]
    }
  }

  const cmd = 'npm ls @syberos/cli -g';
  log.verbose('执行:', cmd)
  shelljs.config.silent = true
  const { stdout } = shelljs.exec(cmd);
  shelljs.config.silent = false
  log.verbose('stdout:', stdout)

  let localVersion;
  const arr = stdout.trim().split('@') || [];
  if (arr.length > 1) {
    localVersion = arr[arr.length - 1]
  }
  log.verbose('localVersion:', localVersion)
  if (localVersion !== remoteVersion) {
    errorLines = [{
      desc: ` ${pkgName}  有新版本`,
      valid: true,
      solution: `请执行升级命令, syberh update self`
    }]
  }
  return {
    desc: '检查@syberos/cli版本',
    lines: errorLines
  }
}

export default checkSyberhPkg
