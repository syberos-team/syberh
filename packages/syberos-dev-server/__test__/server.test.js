var net = require('net')
var path = require('path')
var fs = require('fs-extra')
var port = 8080
var host = '127.0.0.1'

describe('server-test', function () {
  describe('客户端连接', function () {
    let socket = {
      files: null,
      hasSend: 0,
      hasWrite: 0,
      buf: null,
      fd: 'test.zip'
    }
    var client = new net.Socket()
    // 创建socket客户端
    client.setEncoding('binary')
    // 连接到服务端
    client.connect(port, host, function () {
      client.write('hello server')
      // 向端口写入数据到达服务端
    })
    client.on('data', function (data) {
      if (!socket.fileInfo) {
        console.log('-------------data', data)
        const cData = JSON.parse(data)
        socket.fileInfo = cData.files
        console.log(cData.files.length)
        // console.log(cData.fileInfo.name)
        // socket.hasSend = 0 // 已经发送进来的大小
        // socket.hasWrite = 0 // 已经写入的大小
        // socket.buf = '' // buffer存储对象
        // socket.fd = fs.openSync(path.join('.temp', socket.fileInfo.name), 'w+') // 文件标识ID
        client.write('set file info') // 反馈
      } else {
        socket.buf += data
        socket.hasSend = socket.hasSend + data.length
        while (socket.buf.length >= 2048) {
          // 开始重新拼接分块写入，十六进制下字符的大小为之前的二倍
          let pack = socket.buf.slice(0, 2048)
          socket.buf = socket.buf.slice(2048)
          pack = Buffer.from(pack, 'hex')
          // console.log('----pack', pack)
          fs.appendFileSync(socket.fd, pack)
        }
        // console.log(
        //   socket.hasSend,
        //   parseInt((socket.hasSend / 2 / socket.fileInfo.size) * 100) + '%'
        // )
        if (socket.hasSend >= socket.fileInfo.size * 2) {
          // 传输即将完毕，重置
          let buf = Buffer.from(socket.buf, 'hex')
          fs.appendFileSync(socket.fd, buf)
          fs.closeSync(socket.fd)
          console.log('file transfer completed')
          client.write('file transfer completed')
          socket.fileInfo = null
        }
      }
      // console.log('from server:' + data)
      // let buf = Buffer.from(data, 'hex')
      // //console.log(buf)
      // if (!fs.existsSync('socket.fd.zip')) {
      //   fs.appendFileSync('socket.fd.zip', buf)
      //   //得到服务端返回来的数据
      // }
    })
    client.on('error', function (error) {
      // 错误出现之后关闭连接
      console.log('error:' + error)
      client.destory()
    })
    client.on('close', function () {
      // 正常关闭连接
      console.log('Connection closed')
    })
  })
})
