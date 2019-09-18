import * as _ from 'lodash/fp'
import * as npmCheck from 'npm-check'

const isPkgInstalled = _.get('isInstalled')
const isPkgNotInstalled = _.negate(isPkgInstalled)

async function checkPkgs({ appPath }) {
  let errorLines: any[] = []
  const pkgs = await npmCheck({
    cwd: appPath
  })
    .then(_.invoke('all'))
    .then(_.get('packages'))

  errorLines = _.concat(errorLines, pkgsNotInstalled(pkgs))

  return {
    desc: '检查依赖',
    lines: errorLines
  }
}

function pkgsNotInstalled(pkgs) {
  const uninstalledPkgs = _.filter(isPkgNotInstalled, pkgs)
  const lines = _.map(pkg => Object({
    desc: `使用到的依赖 ${pkg.moduleName} 还没有安装`,
    valid: false,
    solution: `请安装依赖, yarn add ${pkg.moduleName}`
  }), uninstalledPkgs)
  return lines
}

export default checkPkgs
