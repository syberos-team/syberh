import * as fs from 'fs-extra'
import * as path from 'path'
import * as childProcess from 'child_process'
import * as chalk from 'chalk'
import * as minimatch from 'minimatch'

import {
  processTypeMap,
  processTypeEnum
} from './constants'
import { ICopyArgOptions, ICopyOptions } from './types'

const execSync = childProcess.execSync


export function promoteRelativePath (fPath: string): string {
  const fPathArr = fPath.split(path.sep)
  let dotCount = 0
  fPathArr.forEach(item => {
    if (item.indexOf('..') >= 0) {
      dotCount++
    }
  })
  if (dotCount === 1) {
    fPathArr.splice(0, 1, '.')
    return fPathArr.join('/')
  }
  if (dotCount > 1) {
    fPathArr.splice(0, 1)
    return fPathArr.join('/')
  }
  return fPath.replace(/\\/g, '/')
}

export function getRootPath (): string {
  return path.resolve(__dirname, '../../')
}

export function getPkgVersion (): string {
  return require(path.join(getRootPath(), 'package.json')).version
}


export function shouldUseYarn (): boolean {
  try {
    execSync('yarn --version', { stdio: 'ignore' })
    return true
  } catch (e) {
    return false
  }
}

export function shouldUseCnpm (): boolean {
  try {
    execSync('cnpm --version', { stdio: 'ignore' })
    return true
  } catch (e) {
    return false
  }
}

export function isEmptyObject (obj: any): boolean {
  if (obj == null) {
    return true
  }
  for (const key in obj) {
    if (obj.hasOwnProperty(key)) {
      return false
    }
  }
  return true
}


export function printLog (type: processTypeEnum, tag: string, filePath?: string) {
  const typeShow = processTypeMap[type]
  const tagLen = tag.replace(/[\u0391-\uFFE5]/g, 'aa').length
  const tagFormatLen = 8
  if (tagLen < tagFormatLen) {
    const rightPadding = new Array(tagFormatLen - tagLen + 1).join(' ')
    tag += rightPadding
  }
  const padding = ''
  filePath = filePath || ''
  if (typeof typeShow.color === 'string') {
    console.log(chalk[typeShow.color](typeShow.name), padding, tag, padding, filePath)
  } else {
    console.log(typeShow.color(typeShow.name), padding, tag, padding, filePath)
  }
}


export function copyFileSync (from: string, to: string, options?: ICopyArgOptions) {
  const filename = path.basename(from)
  if (fs.statSync(from).isFile() && !path.extname(to)) {
    fs.ensureDirSync(to)
    if (from === path.join(to, filename)) {
      return
    }
    return fs.copySync(from, path.join(to, filename), options)
  }
  if (from === to) {
    return
  }
  fs.ensureDirSync(path.dirname(to))
  return fs.copySync(from, to, options)
}

export function copyFiles (appPath: string, copyConfig: ICopyOptions | void) {
  copyConfig = copyConfig || { patterns: [], options: {} }
  if (copyConfig.patterns && copyConfig.patterns.length) {
    copyConfig.options = copyConfig.options || {}
    const globalIgnore = copyConfig.options.ignore
    const projectDir = appPath
    copyConfig.patterns.forEach(pattern => {
      if (pattern.from && pattern.to) {
        const from = path.join(projectDir, pattern.from)
        const to = path.join(projectDir, pattern.to)
        let ignore = pattern.ignore || globalIgnore
        if (fs.existsSync(from)) {
          const copyOptions: ICopyArgOptions = {}
          if (ignore) {
            ignore = Array.isArray(ignore) ? ignore : [ignore]
            copyOptions.filter = src => {
              let isMatch = false
              ignore && ignore.forEach(iPa => {
                if (minimatch(path.basename(src), iPa)) {
                  isMatch = true
                }
              })
              return !isMatch
            }
          }
          copyFileSync(from, to, copyOptions)
        } else {
          printLog(processTypeEnum.ERROR, '拷贝失败', `${pattern.from} 文件不存在！`)
        }
      }
    })
  }
}
