#!/usr/bin/env node

'use strict'

/* eslint-disable no-shadow, no-console */

const Server = require('../dist/index').default
const { gzDir } = require('../dist/util/gzip')
const path = require('path')

let server
const data = { message: 'data' }
function startServer() {
  const wss = new Server({ port: 8080 })

  wss.onConnections(socket => {
    // console.log(JSON.stringify(socket))

    socket.on('close', () => {
      console.log('TCP socket closed')
    })

    socket.on('data', data => {
      console.log('TCP socket on data：', data.toString())
    })
    socket.on('end', () => {
      console.log('TCP socket end')
    })
    const filePath = path.join(path.dirname(path.resolve(__dirname)), 'www')

    console.log(filePath)

    //压缩并发送
    gzDir(filePath).then(ofile => {
      //console.log('---output', ofile)
      setTimeout(() => {
        //console.log('getConnections')
        wss.getConnections(function(error, count) {
          console.log('getConnections', error, count)
        })
        wss.writeFileToClients(ofile)
      }, 1000)
    })
  })

  // server.onConnection(function (c, h) {
  //   console.log('----ok', c);
  //   console.log('----ok', h);
  // })
}

startServer()
