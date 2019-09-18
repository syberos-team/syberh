import * as _ from 'lodash/fp'
import * as npmCheck from 'npm-check'
import * as  latestVersion from 'latest-version'
import log from '../util/log';


// 检查的包的名称
const pkgName = '@syberos/cli';
/**
 * 检查syberh是否需要升级
 */
async function checkSyberhPkg() {

  log.verbose('checkSyberhPkg () start')
  let errorLines: any[] = []


  const remoteVersion = await latestVersion(pkgName);
  log.verbose('remoteVersion:', remoteVersion)
  const pkgs = await npmCheck({
    global: true
  }).then(_.invoke('all'))
    .then(_.get('packages'))

  const localVersion = getLocalVersion(pkgs);
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

function getLocalVersion(pkgs) {
  log.verbose('getLocalVersion() start:', pkgs.length)

  for (let i = 0; i < pkgs.length; i++) {
    if (pkgs[i].moduleName === pkgName) {
      log.verbose('@syberos/cli  package:', JSON.stringify(pkgs[i]));
      return pkgs[i].installed
    }
  }

}

export default checkSyberhPkg
