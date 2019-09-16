
const fs = require('fs-extra')
const path = require('path')
const log = require('./log').default;
const stat = fs.stat

function main () {
  // 定义拷贝的文件或者目录
  const files = [
    'app',
    'com',
    'tests',
    'META-INF',
    'app.pro',
    'sopconfig.xml',
    'syberos.pri'
  ]
  // 获取根目录
  const tempPath = path.resolve('.')
  log.verbose('template路径:', tempPath)
  const copyTo = path.resolve('../cli/templates/default/platforms/syberos')
  fs.emptyDirSync(copyTo)
  log.verbose('cli路径:', copyTo)
  for (let name of files) {
    const src = path.join(tempPath, name)
    copy(src, copyTo)
  }

  const wwwPath = path.join(copyTo, 'app', 'www')
  log.verbose('cli www:', wwwPath)
  const defaulWWW = path.resolve('../cli/templates/default/www')
  log.verbose('cli defaulWWW:', defaulWWW)
  fs.moveSync(wwwPath, defaulWWW, { overwrite: true })
  log.verbose('cli www move 完成')
  log.info('template发布完成')
}
function copy (src, dst) {
  const basename = path.basename(src)
  fs.copySync(src, path.join(dst, basename))
}

main()
