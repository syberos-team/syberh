import * as fs from 'fs-extra'
import * as path from 'path'
import * as shelljs from 'shelljs'
import chalk from 'chalk'
import { AppBuildConfig, DEVICES_TYPES } from '../util/constants'
import * as helper from '../syberos/helper'
import config from '../config/index'
import { log } from '../util/log'

export default class Build {
  private conf: any = {}
  private appPath: string
  // 是否支持cdb
  private isSupportCdb: boolean = false
  // cdb模式的设备名
  private cdbDevice: string
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

  constructor(appPath: string, config: AppBuildConfig) {
    this.appPath = appPath
    this.conf = { ...this.conf, ...config }

    if (log.isVerboseEnabled()) {
      log.verbose('Build constructor(%s, %j)', appPath, config)
      log.verbose('配置参数:%j', this.conf)
    }
    this.pdkRootPath = helper.locatePdk()
    this.targetName = helper.getTargetName(this.appPath, this.conf.adapter)
  }

  /**
   * 开始编译
   */
  public async buildSop() {
    log.verbose('Build buildSop()')
    // 1、生成编译目录
    this.mkdirBuild()
    // 2、拷贝www路径到模板下
    await this.copywww()
    // 3、执行构建命令
    await this.executeShell()

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
   * 开始编译， 并在设备上运行
   */
  public async start() {
    console.log(chalk.green('开始编译'))
    log.verbose('Build start()')
    log.verbose('appPath:%s, conf:%j', this.appPath, this.conf)

    // 执行编译
    await this.buildSop()
    // 安装sop
    await this.installSop()
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
  private async copywww(appPath: string = this.appPath) {
    console.log(chalk.green('准备拷贝www目录'))
    log.verbose('Build copywww(%s)', appPath)
    // const projectName = getProjectName(appPath)
    const wwwPath = path.join(appPath, config.SOURCE_DIR)

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
    const { adapter } = this.conf

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
    // 检查是否支持cdb
    this.checkCdb()
    // 非模拟器，支持cdb
    if (!this.useSimulator && this.isSupportCdb) {
      // 发送
      this.cdbSop(sopPath)
      // 安装
      this.cdbInstallSop(path.basename(sopPath))
      // 启动
      this.cdbStartApp()
    } else {
      // 发送
      this.scpSop(adapterConfig.ip, adapterConfig.port, sopPath)
      // 安装
      this.sshInstallSop(
        adapterConfig.ip,
        adapterConfig.port,
        path.basename(sopPath)
      )
      // 启动
      this.sshStartApp(adapterConfig.ip, adapterConfig.port)
    }
  }

  private checkCdb() {
    log.verbose('Build checkCdb()')
    // 安装至模拟器时，不使用cdb
    if (this.useSimulator) {
      return
    }
    const cdbPath = this.locateCdb()
    log.verbose('%s devices', cdbPath)

    const cdbCmd = `${cdbPath} devices`
    log.verbose('执行：', cdbCmd)
    let result = shelljs.exec(`${cdbPath} devices`)
    log.verbose('执行结果：', result)

    // 出现no permissions时，需要重启cdb服务
    if (result.stdout.indexOf('no permissions') > 0) {
      console.log(chalk.yellow('正在重启cdb服务，启动过程中可能需要输入当前用户的密码...'))

      let cmd = `${cdbPath} kill-server`
      log.verbose('执行：', cmd)
      shelljs.exec(cmd)

      cmd = `sudo ${cdbPath} start-server`
      log.verbose('执行：', cmd)
      shelljs.exec(cmd)

      cmd = `${cdbPath} devices`
      log.verbose('执行：', cmd)
      result = shelljs.exec(cmd)
    }

    this.isSupportCdb = result.stdout.indexOf('-SyberOS') > 0

    const lastIdx = result.stdout.indexOf('-SyberOS')
    const prefixSub = result.stdout.substring(0, lastIdx + 8)
    const firstIdx = prefixSub.lastIndexOf('\n')
    this.cdbDevice = result.stdout.substring(firstIdx + 1, lastIdx + 8)

    log.verbose('isSupportCdb:%s, cdbDevice:%s', this.isSupportCdb, this.cdbDevice)
  }

  private scpSop(ip: string, port: number, sopPath: string) {
    log.verbose('Build scpSop(%s, %d, %s)', ip, port, sopPath)
    console.log(chalk.green('准备发送sop包'))
    log.verbose('ip:%s, port:%d, sopPath:%s', ip, port, sopPath)
    // 非模拟器，支持cdb
    if (!this.useSimulator && this.isSupportCdb) {
      const cdbPath = this.locateCdb()
      const cdbPushCmd = `${cdbPath} -s ${this.cdbDevice} push -p ${sopPath} /tmp`
      log.verbose('执行：', cdbPushCmd)
      shelljs.exec(cdbPushCmd)
    } else {
      const cmd = `expect ${helper.locateScripts('scp-sop.sh')} ${ip} ${port} ${sopPath}`
      log.verbose('执行：', cmd)
      shelljs.exec(cmd)
    }
  }

  private cdbSop(sopPath: string) {
    log.verbose('Build cdbSop(%s)', sopPath)
    const cdbPushCmd = `${this.locateCdb()} -s ${this.cdbDevice} push -p ${sopPath} /tmp`
    log.verbose('执行：', cdbPushCmd)
    shelljs.exec(cdbPushCmd)
  }

  private sshInstallSop(ip: string, port: number, filename: string) {
    log.verbose('Build sshInstallSop(%s, %d, %s)', ip, port, filename)
    console.log(chalk.green('准备安装sop包'))
    log.verbose(filename)

    const nameSplit = filename.split('-')
    const cmd = `expect ${helper.locateScripts('ssh-install-sop.sh')} ${ip} ${port} ${nameSplit[0]} ${filename}`
    log.verbose('执行：', cmd)
    shelljs.exec(cmd)
  }

  private cdbInstallSop(filename: string) {
    log.verbose('Build cdbInstallSop(%s)', filename)
    console.log(chalk.green('准备安装sop包'))
    log.verbose(filename)

    const cmd = `expect ${helper.locateScripts('cdb-install-sop.sh')} ${this.locateCdb()} ${this.cdbDevice} ${filename}`
    log.verbose('执行：', cmd)
    shelljs.exec(cmd)
  }

  private sshStartApp(ip: string, port: number) {
    log.verbose('Build sshStartApp(%s, %d)', ip, port)
    const { sopid, projectName } = this.conf
    console.log(chalk.green('准备启动app'))
    log.verbose('%s:%s:uiapp', sopid, projectName)

    const cmd = `expect ${helper.locateScripts('ssh-start-app.sh')} ${ip} ${port} ${sopid} ${projectName}`
    log.verbose('执行：', cmd)
    shelljs.exec(cmd)
  }

  private cdbStartApp() {
    log.verbose('Build cdbStartApp()')
    const { sopid, projectName } = this.conf
    console.log(chalk.green('准备启动app'))
    log.verbose('%s:%s:uiapp', sopid, projectName)

    const cmd = `expect ${helper.locateScripts('cdb-start-app.sh')} ${this.locateCdb()} ${this.cdbDevice} ${sopid} ${projectName}`
    log.verbose('执行：', cmd)
    shelljs.exec(cmd)
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

    const exConfig = Buffer.from(JSON.stringify(this.conf), 'utf8').toString('hex')
    return `${qmake} ${syberosPro} -r -spec linux-g++ CONFIG+=${qmakeConfig} EX_CONFIG=${exConfig}`
  }

  private makeCommand() {
    log.verbose('Build makeCommand()')
    return '/usr/bin/make'
  }

  private buildPkgCommand() {
    log.verbose('Build buildPkgCommand()')
    const syberosPro = this.locateSyberosPro()
    return `buildpkg ${syberosPro}`
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
  /**
   * 查找cdb路径
   */
  private locateCdb(): string {
    log.verbose('Build locateCdb()')
    return path.join(
      this.pdkRootPath,
      'targets',
      this.targetName,
      'usr',
      'lib',
      'qt5',
      'bin',
      'cdb'
    )
  }
}
