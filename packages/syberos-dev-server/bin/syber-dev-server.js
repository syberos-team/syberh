#!/usr/bin/env node

'use strict'

/* eslint-disable no-shadow, no-console */

const Server = require('../dist/index').default
const { gzDir } = require('../dist/util/gzip')
const path = require('path')
const chokidar = require('chokidar')

function startServer () {
  const wss = new Server({ port: 8080 })
  const dirPath = path.join(path.resolve('.'), 'www')

  const watcher = chokidar.watch(dirPath, {
    ignored: /(^|[/\\])\../,
    persistent: true,
    ignoreInitial: true
  })

  // Something to use when events are received.
  const log = console.log.bind(console)
  // Add event listeners.
  watcher
    .on('add', path => {
      log(`File ${path} has been added`)
      listenerDir(wss, dirPath)
    })
    .on('change', path => {
      log(`File ${path} has been changed`)
      listenerDir(wss, dirPath)
    })
    .on('unlink', path => {
      log(`File ${path} has been removed`)
      listenerDir(wss, dirPath)
    })

  // More possible events.
  watcher
    .on('addDir', path => {
      log(`Directory ${path} has been added`)
      listenerDir(wss, dirPath)
    })
    .on('unlinkDir', path => {
      log(`Directory ${path} has been removed`)
      listenerDir(wss, dirPath)
    })
    .on('error', error => {
      log(`Watcher error: ${error}`)
      // listenerDir(wss, dirPath)
    })
    .on('ready', () => {
      log('Initial scan complete. Ready for changes')
      // listenerDir(wss, dirPath)
    })
    .on('raw', (event, path, details) => {
      // internal
      log('Raw event info:', event, path, details)
    })

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
    setTimeout(() => {
      //  wss.writeFileToClients(filePath)
    }, 1000)
    // // 压缩并发送
    // gzDir(filePath).then(ofile => {
    //   // console.log('---output', ofile)

    // })
  })
}

let setTimeoutTimer = null
function listenerDir (wss, path) {
  console.log('----setTimeoutTimer')
  // 如果开始了,则删除
  if (setTimeoutTimer) {
    clearTimeout(setTimeoutTimer)
    setTimeoutTimer = undefined
  }
  setTimeoutTimer = setTimeout(() => {
    console.log('setTimeoutTimer', setTimeoutTimer)
    wss.writeFileToClients(path)
    clearTimeout(setTimeoutTimer)
    setTimeoutTimer = undefined
  }, 1500)
}

startServer()
