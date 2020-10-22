import * as os from 'os'
import * as fs from 'fs-extra'
import * as readline from 'readline'
import * as path from 'path'
import * as shelljs from 'shelljs'
import { log } from '../util/log'

const homedir = os.homedir()

export type TargetPath = {
  name: string
  path: string
}

interface QtversionsInterface {
  sdkInstallPath(installPath: string): void
  targetInstallPath(targetName: string, installPath: string): void
  getSdkInstallPath(): Promise<string>
  getTargetInstallPath(targetName: string): Promise<string>
  getInstallTargets(): Promise<TargetPath[]>
  getTargetInstallPaths(): Promise<string[]>
  getTargetNames(): Promise<string[]>
}


class Qtversions implements QtversionsInterface {
  private sdkKeyword: string = 'sdk-install-path='
  private path: string

  private _lines : string[] = []

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

  private async readLine(startsWith: string): Promise<string> {
    const lines = await this.readLines();

    for(const line of lines){
      if (line.startsWith(startsWith)) {
        return line;
      }
    }
    return ''
  }

  private async readLines(): Promise<string[]> {
    const useCache = this._lines.length > 0;
    log.verbose(`读取所有行${useCache?'(cache)':''}： ${this.path}`)

    let lines: string[] = []
    if(useCache){
      lines = this._lines
      return new Promise((resolve: (value: string[]) => void): void => {
        resolve(lines)
      })
    }

    return new Promise((resolve: (value: string[]) => void): void => {
      readline.createInterface({
        input: fs.createReadStream(this.path)
      }).on('line', line => {
        lines.push(line)
      }).on('close', () => {
        log.verbose('读取行内容：%j', lines)
        this._lines = lines;
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

  /**
   * 
   * @param targetName e.g. /home/abeir/SyberOS-Pdk
   * @param installPath e.g. target-armv7tnhl-os4_1_1
   * @throws Error
   */
  public targetInstallPath(targetName: string, installPath: string) {
    const key = targetName + '='
    let targetPath = path.join(installPath, 'targets')
    if(!fs.pathExistsSync(targetPath)){
      targetPath = path.join(installPath, 'SyberOS5_0')
      if(!fs.pathExistsSync(targetPath)){
        throw new Error('Cannot find target install folder:' + targetPath);
      }
    }
    const qmakePath = path.join(targetPath, targetName, 'usr/lib/qt5/bin/qmake')
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
      return line.substring(startsWith.length, line.length);
    }
    return ''
  }

  public async getTargetInstallPaths(): Promise<string[]> {
    const lines = await this.readLines()
    const paths: string[] = []
    for (const line of lines) {
      if (!line) {
        continue
      }
      if (line.startsWith(this.sdkKeyword)) {
        continue
      }
      if (!line.startsWith('target-')) {
        continue
      }
      const lineArray = line.split('=')
      if (lineArray && lineArray.length >= 2) {
        paths.push(lineArray[1])
      }
    }
    return paths
  }

  public async getInstallTargets(): Promise<TargetPath[]> {
    const targetPaths: TargetPath[] = []
    const lines = await this.readLines()
    for (const line of lines) {
      if (!line) {
        continue
      }
      if (line.startsWith(this.sdkKeyword)) {
        continue
      }
      if (!line.startsWith('target-')) {
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
    const targetPaths = await this.getInstallTargets()
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
