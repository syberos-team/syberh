const DevServer = require('../dist/build/server').default
const path = require('path')

const apppath = path.resolve('.')
const port = parseInt(process.argv[2])
// 监测www目录的变动
const webPath = process.argv[3]
const watchPath = path.join(apppath, webPath)
console.log('watchPath***', watchPath)
new DevServer({ watchPath, port })
