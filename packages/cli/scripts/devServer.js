const DevServer = require('../dist/build/server').default
const path = require('path')

const apppath = path.resolve('.')
// 监测www目录的变动
const watchPath = path.join(apppath, 'www')
const port = parseInt(process.argv[2])
new DevServer({ watchPath, port })
