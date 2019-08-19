
const fs = require('fs-extra')
const path = require('path')
const stat = fs.stat

function main () {
  // 定义拷贝的文件或者目录
  const files = [
    'app',
    'com',
    'framework',
    'META-INF',
    'app.pro',
    'sopconfig.xml',
    'syberos.pri'
  ]
  // 获取根目录
  const tempPath = path.resolve('.')
  const copyTo = path.resolve('../syberos-cli/templates/default/platforms/syberos')

  fs.ensureDirSync(copyTo)
  console.log('项目路径:', tempPath)
  console.log('拷贝至cli路径:', copyTo)
  for (let name of files) {
    const src = path.join(tempPath, name)
    copy(src, copyTo)
  }

  console.log('拷贝完成')
}

function copy (src, dst) {
  const basename = path.basename(src)
  fs.copySync(src, path.join(dst, basename))
}

main()
