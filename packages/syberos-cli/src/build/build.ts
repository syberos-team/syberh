import * as fs from 'fs-extra'
import * as path from 'path'
import * as shelljs from 'shelljs'
import chalk from 'chalk'
import { AppBuildConfig, DEVICES_TYPES } from '../util/constants'
import * as helper from '../syberos/helper'
import config from '../config/index'

export default class Build {
  private conf: any = {}
  private appPath: string
  // pdk根路径
  private pdkRootPath: string
  private targetName: string
  // 定义编译目录
  private buildDir: string
  // 设备网络配置
  private adapterConfig = {
    device: {
      ip: '192.168.100.100',
      port: 22
    },
    simulator: {
      ip: 'localhost',
      port: 5555
    }
  }

  constructor(appPath: string, config: AppBuildConfig) {
    this.appPath = appPath
    this.conf = { ...this.conf, ...config }
    this.pdkRootPath = helper.locatePdk()
    this.targetName = helper.getTargetName(this.appPath, this.conf.adapter)
  }

  /**
   * 开始编译
   */
  public async start() {
    console.log(chalk.green('开始编译'), this.appPath, JSON.stringify(this.conf))

    // 1、生成编译目录
    this.mkdirBuild()
    // 2、拷贝www路径到模板下
    await this.copywww()
    // 3、执行构建命令
    await this.executeShell()
    // 4、安装sop
    await this.installSop();
  }

  /**
   * 生成编译目录
   */
  private mkdirBuild() {
    console.log(chalk.green('准备编译目录'))
    const appPath = this.appPath
    const { adapter, debug } = this.conf

    // 定义编译目录
    this.buildDir = `${appPath}/.build-${adapter}-${this.targetName}${debug ? '-Debug' : ''}`
    if (!fs.pathExistsSync(this.buildDir)) {
      fs.mkdirsSync(this.buildDir)
    }
    shelljs.cd(this.buildDir)

    console.info('已创建编译目录：', this.buildDir)
  }

  /**
   * 拷贝www路径
   * @param appPath
   */
  private async copywww(appPath: string = this.appPath) {
    console.log(chalk.green('准备拷贝www目录'))
    // const projectName = getProjectName(appPath)
    const wwwPath = path.join(appPath, config.SOURCE_DIR)

    // 模板目录
    const syberosPath = path.join(appPath, 'platforms', 'syberos', 'app', 'www')

    try {
      await fs.emptyDir(syberosPath)
      // 拷贝
      await fs.copy(wwwPath, syberosPath)
    } catch (err) {
      console.error(err)
      return
    }
    console.info('已拷贝www目录，From：', wwwPath, ' To：', syberosPath)
  }
  /**
   * 执行构建脚本
   */
  private async executeShell() {
    console.log(chalk.green('准备执行编译指令'))
    // kchroot qmake
    this.execKchroot(this.qmakeCommand())
    // kchroot make
    this.execKchroot(this.makeCommand())
    // kchroot buildPkg
    this.execKchroot(this.buildPkgCommand())
  }

  /**
   * 安装sop包
   */
  private async installSop() {
    console.log(chalk.green('开始安装sop包...'))
    const { adapter } = this.conf

    let adapterConfig: any

    if (DEVICES_TYPES.DEVICE === adapter) {
      adapterConfig = this.adapterConfig.device
    } else if (DEVICES_TYPES.SIMULATOR === adapter) {
      adapterConfig = this.adapterConfig.simulator
    } else {
      throw new Error('adapter类型错误')
    }

    const { stdout } = shelljs.exec("ls --file-type *.sop |awk '{print i$0}' i=`pwd`'/'")
    const sopPath = stdout.trim()

    // 启动虚拟机
    if (DEVICES_TYPES.SIMULATOR === adapter) {
      console.log(chalk.green('准备启动模拟器'))
      await helper.startvm()
    }
    // 发送
    this.sendSop(adapterConfig.ip, adapterConfig.port, sopPath)
    // 安装
    this.sshInstallSop(adapterConfig.ip, adapterConfig.port, path.basename(sopPath))
    // 启动
    this.sshStartApp(adapterConfig.ip, adapterConfig.port)
  }


  private sendSop(ip: string, port: number, sopPath: string) {
    console.log(chalk.green('准备发送sop包'), ip, port.toString(), sopPath)
    shelljs.exec(`expect ${helper.locateScripts('scp-sop.sh')} ${ip} ${port} ${sopPath}`)
  }

  private sshInstallSop(ip: string, port: number, filename: string) {
    console.log(chalk.green('准备安装sop包'), filename)
    const nameSplit = filename.split('-')
    shelljs.exec(`expect ${helper.locateScripts('ssh-install-sop.sh')} ${ip} ${port} ${nameSplit[0]} ${filename}`)
  }

  private sshStartApp(ip: string, port: number) {
    const { sopid, projectName } = this.conf

    console.log(chalk.green('准备启动app'), sopid + ':' + projectName + ':uiapp')
    shelljs.exec(`expect ${helper.locateScripts('ssh-start-app.sh')} ${ip} ${port} ${sopid} ${projectName}`)
  }


  private execKchroot(subCommand: string = '') {
    const { adapter } = this.conf

    const kchroot = this.locateKchroot()

    let cmd = ''
    if (DEVICES_TYPES.DEVICE === adapter) {
      // 真机
      cmd += `${kchroot} 'sb2 -t ${this.targetName} -R'`
    } else if (DEVICES_TYPES.SIMULATOR === adapter) {
      // 模拟器
      cmd += `${kchroot} exec_${this.targetName}`
    } else {
      throw new Error('adapter类型错误')
    }

    if (cmd) {
      if (subCommand) {
        cmd += ` '${subCommand}'`
      }
      console.info('执行指令：', cmd)
      shelljs.exec(cmd)
    }
  }

  private qmakeCommand() {
    const { debug } = this.conf

    const qmake = this.locateQmake()
    const syberosPro = this.locateSyberosPro()

    const qmakeConfig = debug ? 'qml_debug' : 'release'

    const exConfig = Buffer.from(JSON.stringify(this.conf), 'utf8').toString('hex')
    return `${qmake} ${syberosPro} -r -spec linux-g++ CONFIG+=${qmakeConfig} EX_CONFIG=${exConfig}`
  }

  private makeCommand() {
    return '/usr/bin/make'
  }

  private buildPkgCommand() {
    const syberosPro = this.locateSyberosPro()
    return `buildpkg ${syberosPro}`
  }

  /**
   * 查找kchroot路径
   */
  private locateKchroot(): string {
    return path.join(this.pdkRootPath, 'sdk', 'script', 'kchroot')
  }
  /**
   * 查找qmake路径
   */
  private locateQmake(): string {
    return path.join(this.pdkRootPath, 'targets', this.targetName, 'usr', 'lib', 'qt5', 'bin', 'qmake')
  }
  /**
   * 查找项目中的syberos.pro文件路径
   */
  private locateSyberosPro(): string {
    return path.join(this.appPath, 'platforms', 'syberos', 'syberos.pro')
  }
}
