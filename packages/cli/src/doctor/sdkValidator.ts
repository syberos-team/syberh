import * as path from 'path'
import * as  fs from 'fs-extra'
import { getRootPath } from '../util/index';
import log from '../util/log';


function getTemplatePath(template = 'default') {
  return path.join(getRootPath(), 'templates', template)
}
/**
 * 检查SDK是否为最新是否需要升级
 */
async function checkSdk() {
  log.verbose('checkSdk()')

  const errorLines: any[] = []
  const vpath = path.join(path.resolve('.'), 'platforms', 'syberos', 'VERSION')
  log.verbose('vpath', vpath)
  if (!fs.existsSync(vpath)) {
    log.verbose('文件不存在', vpath)
    errorLines.push({
      desc: ` sdk 有新版本`,
      valid: true,
      solution: `请执行升级命令: syberh update project`
    })
  } else {
    try {
      const projectVConfig = fs.readJSONSync(vpath);
      log.verbose('projectVConfig', JSON.stringify(projectVConfig))
      const cliVersionPath = path.join(getTemplatePath(), 'platforms', 'syberos', 'VERSION');
      log.verbose('cliVersionPath', cliVersionPath)
      if (!fs.existsSync(cliVersionPath)) {
        errorLines.push({
          desc: ` CLI 中VERSION不存在`,
          valid: false
        })
      } else {
        const cliVersionConfig = fs.readJSONSync(cliVersionPath);
        log.verbose('cliVersionConfig', JSON.stringify(cliVersionConfig))
        if (cliVersionConfig.version !== projectVConfig.version) {
          errorLines.push({
            desc: ` sdk 有新版本`,
            valid: true,
            solution: `请执行升级命令:  syberh update project`
          })
        }
      }

    } catch (err) {
      errorLines.push({
        desc: ` sdk 检查出错`,
        valid: false,
        solution: JSON.stringify(err)
      })
    }

  }

  return {
    desc: '检查SDK版本',
    lines: errorLines
  }
}


export default checkSdk
