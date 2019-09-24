const DevServer = require('../dist/build/server').default
const path = require('path')

const apppath = path.resolve('.')
// 监测www目录的变动
const wathcPath = path.join(apppath, 'www')
const port = parseInt(process.argv[2])
console.log('-------------port---------', port)
new DevServer({ wathcPath, port })
