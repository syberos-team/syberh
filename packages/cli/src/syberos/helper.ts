import * as fs from 'fs-extra'
import * as path from 'path'
import { PROJECT_CONFIG, DEVICES_TYPES } from '../util/constants'
import { getRootPath } from '../util/index'
import * as shelljs from 'shelljs'
import chalk from 'chalk'
import { qtversions } from './configfile'
import { ChildProcess } from 'child_process'

/**
 *  读取project.config.json配置文件
 * @param appPath
 * @return project.config.json
 */
export const getProjectConfig = (appPath: string) => {
  try {
    return fs.readJSONSync(path.join(appPath, PROJECT_CONFIG))
  } catch (error) {
    console.error('读取配置文件失败', JSON.stringify(error))
    throw new Error(`${PROJECT_CONFIG} 不存在`)
  }
}

/**
 * 获取项目名称
 * @param appPath
 * @return string
 */
export const getProjectName = (appPath: string) => {
  const { projectName } = getProjectConfig(appPath)
  return projectName
}

/**
 * 获取ProjectConfig 配置文件中的target
 * @param appPath
 * @param targetName
 * @return string 返回target name
 *
 */
export const getTargetName = (appPath: string, adapter?: DEVICES_TYPES) => {
  const projectConfig = getProjectConfig(appPath)

  if (adapter === DEVICES_TYPES.SIMULATOR) {
    return projectConfig.targetSimulator
  }

  if (adapter === DEVICES_TYPES.DEVICE) {
    return projectConfig['target']
  }

  return projectConfig['target']
  // throw new Error(`${PROJECT_CONFIG} 配置文件未找到`)
}

/**
 * 查找已安装的所有target，若未找到任何target则返回空数组
 */
export async function findTargets(): Promise<string[]> {
  const targetNames: string[] = []
  const targetFullNames = await qtversions.getTargetNames()
  if (!targetFullNames || targetFullNames.length === 0) {
      return targetNames
  }
  for (const targetName of targetFullNames) {
      const name = targetName;
      if (!targetNames.includes(name)) {
        targetNames.push(name)
      }
  }
  return targetNames;
}

/**
 * 主进程休眠
 * @param ms 休眠时长（毫秒）
 */
export const sleep = (ms: number) => {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      try {
        resolve(1)
      } catch (e) {
        reject(e)
      }
    }, ms)
  })
}

/**
 * 获取当前用户home目录下的子目录的路径
 * @param subDirs home目录下的子目录名
 */
export const homeSubPath = (...subDirs: string[]): string => {
  const { stdout } = shelljs.exec(`env | grep ^HOME= | cut -c 6-`)
  const subDirPath = path.join(stdout.trim(), ...subDirs)
  const existe = fs.pathExists(subDirPath)
  if (!existe) {
    throw new Error(`根目录下未找到${path.join(...subDirs)}目录`)
  }
  return subDirPath
}

/**
 * 查找pdk根目录路径
 */
let _sdkPathPromise: Promise<string>
export const locateSdk = (): Promise<string> => {
  if (!_sdkPathPromise) {
    _sdkPathPromise = qtversions.getSdkInstallPath()
  }
  return _sdkPathPromise
}

export const locateAllTarget = (): Promise<string[]> => {
  return qtversions.getTargetInstallPaths()
}

export const locateIde = (): string => {
  return homeSubPath('SyberOS-SDK')
}

/**
 * 查找sh脚本路径
 * @param shFilename sh脚本文件吗
 */
export const locateScripts = (shFilename: string): string => {
  return path.join(getRootPath(), 'scripts', shFilename)
}

/**
 * 启动模拟器
 * @param port  模拟器ssh端口，默认5555
 */
export const startvm = async (port: number | string = 5555) => {
  const emulatorPath = path.join(locateIde(), 'emulator')
  console.log(`模拟器<${port}>：${emulatorPath}`)

  const pid = shelljs.exec('pgrep "emulator-x86"')
  if (pid.trim()) {
    console.log(chalk.blue(`模拟器正在运行[pid=${pid.trim()}]`))
    return
  }

  const result = shelljs.exec(`${locateScripts('startvm.sh')} ${emulatorPath} ${port || ''}`)
  if (result.code === 1) {
    await sleep(2000)
    console.log(chalk.blue(`模拟器已启动[pid=${shelljs.exec('pgrep "emulator-x86"').trim()}]`))
  } else if (result.code === 2) {
    console.log(chalk.red('启动模拟器失败'))
  }
}

/**
 * 执行shell命令
 * @param cmd 
 */
export const runShell = (cmd: string, retry: boolean = true) => {
  const result = shelljs.exec(cmd)
  const out = result.stdout
  if (out.includes('WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED')) {
    const lines = out.split('\n')

    let rmKeyCmd: string = ''
    for(const line of lines){
      if(line.indexOf('ssh-keygen -f') >= 0){
        rmKeyCmd = line.trim()
        break
      }
    }
    if(rmKeyCmd){
      console.log('执行：', rmKeyCmd)
      shelljs.exec(rmKeyCmd)
    }
    // 再次尝试执行
    if(retry){
      console.log('再次执行：', cmd)
      shelljs.exec(cmd)
    }
  }
}

const sudoPasswordCommand = (password:string) => {
  return `expect<<EOF
spawn sudo echo "test password"
expect {
    "sudo" {
        send "${password}\r"
        exp_continue
    } eof {
        send_user "failed\n"
        exit
    }
    "test password" { 
        send_user "successed\n"
    }
}
expect eof
EOF`
}

/**
 * 同步校验当前用户密码
 */
export const checkSudoPassword = (password: string) : boolean | Promise<boolean> => {
  if(!password){
    return false
  }
  const cmd = sudoPasswordCommand(password)

  shelljs.config.silent = true
  const result = shelljs.exec(cmd)
  shelljs.config.silent = false
  return result.stdout.includes('successed')
}

/**
 * 异步校验当前用户密码
 */
export const checkSudoPasswordAsync = (password: string) : Promise<boolean> => {
  return new Promise<boolean>((resolve, reject)=>{
    if(!password){
      resolve(false)
      return
    }
    const cmd = sudoPasswordCommand(password)

    shelljs.config.silent = true
    const childProcess: ChildProcess = shelljs.exec(cmd, {async: true})

    let isValid: boolean = false
    childProcess.stdout?.on('data', (data) =>{
      if(typeof data === 'string'){
        isValid = data.includes('successed')
      }
    })
    childProcess.on('exit', () => {
      shelljs.config.silent = false
      resolve(isValid)
    })
    childProcess.on('error', (code) => {
      shelljs.config.silent = false
      reject(code)
    })
  })
}

/**
 * 根据target判断是否是os5
 * 目前根据target名称结尾是否存在5_0字符串，以后可能需要修改判断
 * @param targetName 
 */
export const isTargetOS_5 = (targetName: string): boolean => {
  if(!targetName){
    return false;
  }
  return targetName.endsWith('5_0');
}
