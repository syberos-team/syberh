import * as os from 'os'
import * as fs from 'fs-extra'
import * as readline from 'readline'
import * as path from 'path'
import * as shelljs from 'shelljs'
import { log } from '../util/log'

const homedir = os.homedir()

type TargetPath = {
  name: string
  path: string
}

interface QtversionsInterface {
  sdkInstallPath(installPath: string): void
  targetInstallPath(targetName: string, installPath: string): void
  getSdkInstallPath(): Promise<string>
  getTargetInstallPath(targetName: string): Promise<string>
  getTargetInstallPaths(): Promise<TargetPath[]>
  getTargetNames(): Promise<string[]>
}


class Qtversions implements QtversionsInterface {
  private sdkKeyword: string = 'sdk-install-path='
  private path: string

  constructor() {
    this.path = this.getPath(homedir)
  }

  /**
   * 获取.config/qtversions.conf文件路径，若文件不存在会创建该文件
   */
  private getPath(home: string): string {
    const dirPath = path.join(home, '.config')
    if (!fs.pathExistsSync(dirPath)) {
      fs.mkdirsSync(dirPath)
    }
    const filePath = path.join(dirPath, 'qtversions.conf')
    if (!fs.existsSync(filePath)) {
      fs.createFileSync(filePath)
    }
    return filePath
  }

  public setPath(path: string) {
    this.path = path
  }

  private readReplace(key: string, installPath: string): Promise<string[]> {
    log.verbose('读取：', this.path)
    // key 是否存在文件中
    let isKeyExist = false
    const lines: string[] = []
    return new Promise((resolve: (value: string[]) => void): void => {
      readline.createInterface({
        input: fs.createReadStream(this.path)
      }).on('line', line => {
        if (line.startsWith(key)) {
          isKeyExist = true
          lines.push(key + installPath)
        } else {
          lines.push(line)
        }
      }).on('close', () => {
        // 文件无内容或者没有对应的key时，添加
        if (lines.length === 0 || !isKeyExist) {
          lines.push(key + installPath)
        }
        log.verbose('写入内容：%j', lines)
        resolve(lines)
      })
    })
  }

  private readLine(startsWith: string): Promise<string> {
    log.verbose('读取行：', this.path)
    let lineContent: string
    return new Promise((resolve: (value: string) => void): void => {
      readline.createInterface({
        input: fs.createReadStream(this.path)
      }).on('line', line => {
        if (line.startsWith(startsWith)) {
          lineContent = line
        }
      }).on('close', () => {
        log.verbose('读取行内容：%s', lineContent)
        resolve(lineContent)
      })
    })
  }

  private async readLines(): Promise<string[]> {
    log.verbose('读取所有行：', this.path)
    const lines: string[] = []
    return new Promise((resolve: (value: string[]) => void): void => {
      readline.createInterface({
        input: fs.createReadStream(this.path)
      }).on('line', line => {
        lines.push(line)
      }).on('close', () => {
        log.verbose('读取行内容：%j', lines)
        resolve(lines)
      })
    })
  }

  private flush(lines: string[]) {
    fs.writeFileSync(this.path, lines.join('\n'))
  }


  public sdkInstallPath(installPath: string) {
    const key = this.sdkKeyword
    this.readReplace(key, installPath).then(lines => {
      this.flush(lines)
    })
  }

  public targetInstallPath(targetName: string, installPath: string) {
    const key = targetName + '='
    const qmakePath = path.join(installPath, 'targets', targetName, 'usr/lib/qt5/bin/qmake')
    this.readReplace(key, qmakePath).then(lines => {
      this.flush(lines)
    })
  }

  public async getSdkInstallPath(): Promise<string> {
    const startsWith = 'sdk-install-path='
    const line = await this.readLine(startsWith)
    if (line) {
      return line.substring(startsWith.length, line.length)
    }
    return ''
  }

  public async getTargetInstallPath(targetName: string): Promise<string> {
    const startsWith = targetName + '='
    const line = await this.readLine(startsWith)
    if (line) {
      return line.substring(startsWith.length, line.length)
    }
    return ''
  }

  public async getTargetInstallPaths(): Promise<TargetPath[]> {
    const lines = await this.readLines()
    const targetPaths: TargetPath[] = []
    for (const line of lines) {
      if (!line) {
        continue
      }
      if (line.startsWith(this.sdkKeyword)) {
        continue
      }
      const lineArray = line.split('=')
      if (lineArray && lineArray.length >= 2) {
        targetPaths.push({
          name: lineArray[0],
          path: lineArray[1]
        })
      }
    }
    return targetPaths
  }

  public async getTargetNames(): Promise<string[]> {
    const targetPaths = await this.getTargetInstallPaths()
    const targetNames: string[] = []
    for (const targetPath of targetPaths) {
      targetNames.push(targetPath.name)
    }
    return targetNames
  }

}

class Scratchbox2 {
  private path: string

  constructor() {
    this.path = this.getPath(homedir)
  }

  private getPath(home: string): string {
    const dirPath = path.join(home, '.scratchbox2')
    if (!fs.pathExistsSync(dirPath)) {
      fs.mkdirsSync(dirPath)
    }
    return dirPath
  }

  /**
   * 拷贝scratchbox2目录
   * @param targetName 
   * @param installPath 
   */
  public copyDir(targetName: string, installPath: string) {
    const src = path.join(installPath, 'targets', targetName, 'scratchbox2/*')
    shelljs.cp('-r', src, this.path)
  }
}


export const qtversions = new Qtversions()
export const scratchbox2 = new Scratchbox2()
