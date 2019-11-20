import * as fs from 'fs-extra'
import * as path from 'path'
import * as shelljs from 'shelljs'
import * as os from 'os'
import chalk from 'chalk'
import { AppBuildConfig, DEVICES_TYPES } from '../util/constants'
import * as helper from '../syberos/helper'
import config from '../config/index'
import { log } from '../util/log'
import * as sop from './sop'
import * as connect from './connect'

export default class Build {
  // 日志级别
  private devLog: string = process.env.DEV_LOG || 'info'

  private conf: any = {}
  private appPath: string
  private webPath: string

  // pdk根路径
  private pdkRootPath: string
  private targetName: string
  // 定义编译目录
  private buildDir: string
  // 是否安装至模拟器
  private useSimulator: boolean = false
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

  constructor(appPath: string, webPath: string, config: AppBuildConfig) {
    this.appPath = appPath
    this.webPath = webPath
    this.conf = { ...this.conf, ...config }

    if (log.isVerboseEnabled()) {
      log.verbose('Build constructor(%s, %j)', appPath, webPath, config)
      log.verbose('配置参数:%j', this.conf)
    }
    this.targetName = helper.getTargetName(this.appPath, this.conf.adapter)
  }

  /**
   * 开始编译， 并在设备上运行
   */
  public async start(buildSuccessCallback) {
    log.verbose('Build start()')

    this.pdkRootPath = await helper.locateSdk()
    log.verbose('pdkRootPath:', this.pdkRootPath)

    // 检查设备连接
    this.checkConnect(this.pdkRootPath, this.targetName)

    console.log(chalk.green('开始编译'))
    log.verbose('appPath:%s, conf:%j', this.appPath, this.conf)

    // 执行编译
    await this.buildSop(buildSuccessCallback)
    // 安装sop
    await this.installSop()
  }

  /**
   * 检查手机是否连接
   */
  private checkConnect(pdkRootPath: string, targetName: string) {
    log.verbose('Build checkConnect(%s, %s)', pdkRootPath, targetName)
    const { adapter } = this.conf
    if (DEVICES_TYPES.DEVICE !== adapter) {
      log.verbose('当前设备类型为：%s, 无须检查设备连接')
      return
    }
    const checker = new connect.ConnectChecker(pdkRootPath, targetName)
    if (checker.isCdbEnabled() || checker.isSshEnabled(this.adapterConfig.device.ip, this.adapterConfig.device.port)) {
      return
    }
    console.log(chalk.red('未检测到设备'))
    process.exit(0)
  }

  /**
   * 开始编译
   */
  public async buildSop(buildSuccessCallback) {
    log.verbose('Build buildSop()')
    this.pdkRootPath = await helper.locateSdk()
    // 1、生成编译目录
    this.mkdirBuild()
    // 2、拷贝www路径到模板下
    await this.copywww()
    // 3、执行构建命令
    await this.executeShell()
    // 4、构建完成后执行回调
    if (typeof buildSuccessCallback === 'function') {
      buildSuccessCallback.call(this)
    }

    if (this.conf.onlyBuildSop === true) {
      const cmd = "ls --file-type *.sop |awk '{print i$0}' i=`pwd`'/'"
      log.verbose('执行：', cmd)
      const { stdout } = shelljs.exec(cmd)
      log.verbose('执行结果：', stdout)

      const sopPath = stdout.trim()
      console.log(chalk.blue('打包完成，SOP包的位置是=>'), sopPath)
      shelljs.exit(0)
    }
  }

  /**
   * 生成编译目录
   */
  private mkdirBuild() {
    console.log(chalk.green('准备编译目录'))
    log.verbose('Build mkdirBuild()')
    const appPath = this.appPath
    const { adapter, debug, onlyBuildSop } = this.conf

    // 定义编译目录
    if (onlyBuildSop === true) {
      // 如果是只打SOP包， 目录名的设备名为 device
      this.buildDir = `${appPath}/.build-${DEVICES_TYPES.DEVICE}-${
        this.targetName
        }${debug ? '-Debug' : ''}`
    } else {
      this.buildDir = `${appPath}/.build-${adapter}-${this.targetName}${
        debug ? '-Debug' : ''
        }`
    }

    if (!fs.pathExistsSync(this.buildDir)) {
      fs.mkdirsSync(this.buildDir)
    }
    shelljs.cd(this.buildDir)

    log.info('已创建编译目录：', this.buildDir)
  }

  /**
   * 拷贝www路径
   * @param appPath
   */
  private async copywww(appPath: string = this.appPath, webPath: string = this.webPath) {
    console.log(chalk.green('准备拷贝www目录'))
    log.verbose('Build copywww(%s)', appPath)
    // const projectName = getProjectName(appPath)
    const wwwPath = path.join(appPath, webPath || config.SOURCE_DIR)

    // 模板目录
    const syberosPath = path.join(appPath, 'platforms', 'syberos', 'app', 'www')

    try {
      await fs.emptyDir(syberosPath)
      // 拷贝
      await fs.copy(wwwPath, syberosPath)
    } catch (err) {
      log.error(chalk.red(err))
      return
    }
    log.info('已拷贝www目录，From：', wwwPath, ' To：', syberosPath)
  }
  /**
   * 执行构建脚本
   */
  private async executeShell() {
    log.verbose('Build executeShell()')
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
    log.verbose('Build installSop()')
    console.log(chalk.green('开始安装sop包...'))
    const { adapter, sopid, projectName } = this.conf

    let adapterConfig: any
    // 检查安装至模拟器还是真机
    if (DEVICES_TYPES.DEVICE === adapter) {
      adapterConfig = this.adapterConfig.device
    } else if (DEVICES_TYPES.SIMULATOR === adapter) {
      adapterConfig = this.adapterConfig.simulator
      this.useSimulator = true
    } else {
      throw new Error('adapter类型错误')
    }

    const cmd = "ls --file-type *.sop |awk '{print i$0}' i=`pwd`'/'"
    log.verbose('执行：', cmd)
    const { stdout } = shelljs.exec(cmd)
    log.verbose('执行结果：', stdout)

    const sopPath = stdout.trim()

    // 启动虚拟机
    if (DEVICES_TYPES.SIMULATOR === adapter) {
      console.log(chalk.green('准备启动模拟器'))
      await helper.startvm()
    }

    const cdbSop = new sop.CdbSop(this.pdkRootPath, this.targetName, sopid, projectName)
    // 非模拟器，支持cdb
    if (!this.useSimulator && cdbSop.isSupportCdb()) {
      // 发送
      cdbSop.send(sopPath)
      // 安装
      cdbSop.install(path.basename(sopPath))
      // 启动
      cdbSop.startApp()
    } else {
      const sshSop = new sop.SshSop(adapterConfig.ip, adapterConfig.port, sopid, projectName)
      // 发送
      sshSop.send(sopPath)
      // 安装
      sshSop.install(path.basename(sopPath))
      // 启动
      sshSop.startApp()
    }
  }

  private execKchroot(subCommand: string = '') {
    log.verbose('Build execKchroot()', subCommand)
    const { adapter, onlyBuildSop } = this.conf

    const kchroot = this.locateKchroot()

    let cmd = ''
    if (DEVICES_TYPES.DEVICE === adapter) {
      // 真机
      cmd += `${kchroot} 'sb2 -t ${this.targetName} -R'`
    } else if (DEVICES_TYPES.SIMULATOR === adapter) {
      // 模拟器
      cmd += `${kchroot} exec_${this.targetName}`
    } else if (onlyBuildSop === true) {
      // 打SOP包， 和真机命令一样
      cmd += `${kchroot} 'sb2 -t ${this.targetName} -R'`
    } else {
      throw new Error('adapter类型错误')
    }

    if (cmd) {
      if (subCommand) {
        cmd += ` '${subCommand}'`
      }
      log.verbose('执行：', cmd)
      shelljs.exec(cmd)
    }
  }

  private qmakeCommand() {
    log.verbose('Build qmakeCommand()')
    const { debug } = this.conf

    const qmake = this.locateQmake()
    const syberosPro = this.locateSyberosPro()

    const qmakeConfig = debug ? 'qml_debug' : 'release'

    const exConfigObj = { ...this.conf }
    exConfigObj.DEV_LOG = this.devLog

    log.verbose('扩展参数：%j', exConfigObj)
    const exConfig = Buffer.from(JSON.stringify(exConfigObj), 'utf8').toString(
      'hex'
    )
    return `${qmake} ${syberosPro} -r -spec linux-g++ CONFIG+=${qmakeConfig} EX_CONFIG=${exConfig}`
  }

  private makeCommand() {
    log.verbose('Build makeCommand()')
    const cpu = this.getCpu()
    const cmd = `/usr/bin/make -j${cpu} `
    log.verbose('Build makeCommand() cmd:', cmd)
    return cmd
  }

  private buildPkgCommand() {
    log.verbose('Build buildPkgCommand()')
    const syberosPro = this.locateSyberosPro()
    return `buildpkg ${syberosPro}`
  }

  /**
   * 获取CUP进程数
   */
  private getCpu() {
    log.verbose('Build getCpu()')
    let ret: any = 4
    try {
      ret = os.cpus().length
      log.verbose(chalk.green(`getCpu() length :${ret}`))
    } catch (e) {
      log.error('getCpu', e)
    }
    return ret
  }

  /**
   * 查找kchroot路径
   */
  private locateKchroot(): string {
    log.verbose('Build locateKchroot()')
    return path.join(this.pdkRootPath, 'sdk', 'script', 'kchroot')
  }
  /**
   * 查找qmake路径
   */
  private locateQmake(): string {
    log.verbose('Build locateQmake()')
    return path.join(
      this.pdkRootPath,
      'targets',
      this.targetName,
      'usr',
      'lib',
      'qt5',
      'bin',
      'qmake'
    )
  }
  /**
   * 查找项目中的syberos.pro文件路径
   */
  private locateSyberosPro(): string {
    log.verbose('Build locateSyberosPro()')
    return path.join(this.appPath, 'platforms', 'syberos', 'app.pro')
  }

}
