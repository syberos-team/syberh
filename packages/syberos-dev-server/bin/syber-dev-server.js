#!/usr/bin/env node

'use strict'

/* eslint-disable no-shadow, no-console */

const Server = require('../dist/index').default
const { Watcher } = require('../dist/index')
const path = require('path')

function startServer () {
  const wss = new Server({ port: 4399 })
  const dirPath = path.join(path.resolve('.'), 'www')

  new Watcher(wss, dirPath)
}

startServer()
