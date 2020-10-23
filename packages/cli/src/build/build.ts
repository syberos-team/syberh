import * as fs from 'fs-extra'
import * as path from 'path'
import * as shelljs from 'shelljs'
import chalk from 'chalk'
import { DEVICES_TYPES } from '../util/constants'
import * as helper from '../syberos/helper'
import config from '../config/index'
import { log } from '../util/log'
import * as sop from './sop'
import * as connect from './connect'
import * as compile from './compile'
import * as cert from './cert'
import { BuildConfig, ExConfig } from './types'
import { IProjectConfig } from '../util/types'

// 设备网络配置
const adapterConfig = {
  simulator: {
    ip: 'localhost',
    port: '5555'
  }
}

export type BuildSuccessCallback = () => void

export class Build {
  // 日志级别
  private devLog: string = process.env.DEV_LOG || 'info'

  private appPath : string
  private buildConfig : BuildConfig
  private projectConfig : IProjectConfig

  // pdk根路径
  private pdkRootPath: string
  // 定义编译目录
  private buildDir: string
  // 是否安装至模拟器
  private useSimulator: boolean = false

  constructor(appPath: string, projectConf : IProjectConfig, config: BuildConfig) {
    this.appPath = appPath
    this.projectConfig = projectConf
    this.buildConfig = config

    if (log.isVerboseEnabled()) {
      log.verbose('Build constructor()', appPath, JSON.stringify(projectConf), JSON.stringify(config))
    }
    // 检查安装至模拟器还是真机
    if (DEVICES_TYPES.SIMULATOR === this.buildConfig.type) {
      this.useSimulator = true
    }
  }

  /**
   * 开始编译， 并在设备上运行
   */
  public async start(buildSuccessCallback: BuildSuccessCallback | null) {
    log.verbose('Build start()')

    this.pdkRootPath = await helper.locateSdk()
    log.verbose('pdkRootPath:', this.pdkRootPath)

    // 当不设置仅编译参数时，检查设备连接
    if (!this.buildConfig.onlyBuild) {
      this.checkConnect()
    }

    console.log(chalk.green('开始编译'))
    log.verbose('appPath:%s, conf:%j', this.appPath, this.buildConfig)

    // 执行编译
    const sopPath = await this.buildSop(buildSuccessCallback)

    // 设置仅编译参数时，不安装sop
    if (this.buildConfig.onlyBuild) {
      console.log(chalk.blue('打包完成，SOP包的位置是=>'), sopPath)
      return;
    }
    // 安装sop
    await this.installSop(sopPath)
  }

  /**
   * 检查手机是否连接
   */
  private checkConnect() {
    log.verbose('Build checkConnect(%s, %s)', this.pdkRootPath, this.projectConfig.target)
    const { type } = this.buildConfig
    if (DEVICES_TYPES.DEVICE !== type) {
      log.verbose('当前设备类型为：%s, 无须检查设备连接')
      return
    }
    const checker = new connect.ConnectChecker(this.pdkRootPath, this.projectConfig.target)
    if (checker.isCdbEnabled() || checker.isSshEnabled(this.projectConfig.deployIP, this.projectConfig.deployPort)) {
      return
    }
    console.log(chalk.red('未检测到设备'))
    process.exit(0)
  }

  /**
   * 开始编译
   */
  public async buildSop(buildSuccessCallback: BuildSuccessCallback | null): Promise<string | null> {
    log.verbose('Build buildSop()')

    this.pdkRootPath = await helper.locateSdk()
    // 1、生成编译目录
    this.mkdirBuild()
    // 2、拷贝www路径到模板下
    await this.copywww()
    // 3、在platforms/syberos目录下生成project.config.json
    this.generateProjectConfig();
    // 4、生成证书
    this.generateCert();
    // 5、执行构建命令
    const sopPath = this.compile()
    // 6、构建完成后执行回调
    if (typeof buildSuccessCallback === 'function') {
      // 构建完成后，回退到项目根目录
      shelljs.cd('..')
      buildSuccessCallback.call(this)
    }
    return sopPath;
  }

  /**
   * 生成编译目录
   */
  private mkdirBuild() {
    console.log(chalk.green('准备编译目录'))
    log.verbose('Build mkdirBuild()')

    // 定义编译目录
    if (this.buildConfig.onlyBuild === true) {
      // 如果是只打SOP包， 目录名的设备名为 device
      this.buildDir = `${this.appPath}/.build-${DEVICES_TYPES.DEVICE}-${this.projectConfig.target}${this.buildConfig.release ? '' : '-Debug'}`
    } else {
      this.buildDir = `${this.appPath}/.build-${this.buildConfig.type}-${this.projectConfig.target}${this.buildConfig.release ? '' : '-Debug'}`
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
  private async copywww() {
    console.log(chalk.green('准备拷贝www目录'))
    log.verbose('Build copywww(%s)', this.appPath)

    const wwwPath = path.join(this.appPath, this.projectConfig.webPath || config.SOURCE_DIR)

    // 模板目录
    const syberosPath = path.join(this.appPath, 'platforms', 'syberos', 'app', 'www')
    try {
      // 清空www目录
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
   * 在platforms/syberos目录下生成project.config.json
   */
  private generateProjectConfig(){
    const projectConfObj : ExConfig = { 
      debug: !this.buildConfig.release,
      logLevel: this.devLog,
      ...this.projectConfig
    }
    const projectConfigPath = path.join(this.appPath, 'platforms/syberos/project.config.json');

    fs.writeJSONSync(projectConfigPath, projectConfObj);
    log.info('生成配置：', projectConfigPath)
  }

  /**
   * 生成证书
   */
  private generateCert(){
    log.verbose('Build generateCert()')
    console.log(chalk.green('准备生成证书'))

    const certGenerator = new cert.CertGenerator({
      appPath: this.appPath,
      targetName: this.projectConfig.target
    });
    try{
      const certPath = certGenerator.generate();
      log.info('已生成证书：', certPath);
    }catch(e){
      if(e instanceof cert.CertError){
        log.warn(e.getMessage());
      }
    }
  }

  /**
   * 执行构建，检查lib中是否已存在需要的库，若不存在时先编译一次syberh应用生成so，之后编译插件，再编译syberh
   * 编译成功返回sop路径，失败时返回null
   */
  private async compile(): Promise<string | null> {
    log.verbose('Build compile()')
    console.log(chalk.green('准备执行编译指令'))

    const compiler = new compile.Compiler()

    const platformsSyberosPath = path.join(this.appPath, 'platforms/syberos');
    // syberh-plugins是否存在，不存在时只编译syberh应用
    const existsSyberhPlugins = compiler.isSyberhPluginsExists(platformsSyberosPath);
    if (!existsSyberhPlugins) {
      try {
        const sopPath = await this.compileApp(true);
        log.info('编译完成，sop：', sopPath);
        return sopPath;
      } catch (e) {
        log.error('编译syberh应用失败: ', e)
        return null;
      }
    }
    // syberh-plugins存在，需要编译插件
    try {
      if (!compiler.existsLib(platformsSyberosPath)) {
        log.verbose('lib中未找到so，编译插件前先编译一次应用')
        this.compileApp(false);
      }
      this.compilePlugins();
      const sopPath = await this.compileApp(true);
      log.info('编译完成，sop：', sopPath);
      return sopPath;
    } catch (e) {
      log.error('编译失败: ', e)
    }
    return null;
  }

  /**
   * 编译syberh应用
   * @param buildPkg 是否需要打sop包
   */
  private async compileApp(buildPkg: boolean): Promise<string | null> {
    log.verbose('Build compileApp(%s)', buildPkg)

    const compiler = new compile.Compiler()
    const compileResult = await compiler.buildApp({
      // 编译项目的pro文件位置
      proPath: path.join(this.appPath, 'platforms/syberos/app.pro'),
      // 编译输出目录
      buildPath: this.buildDir,
      // pdk命令所在位置
      pdkPath: this.pdkRootPath,
      // target完整名称：target-armv7tnhl-xuanwu
      targetName: this.projectConfig.target,
      // 额外的qmake编译参数
      qmakeArgs: [],
      // 是否使用debug编译
      debug: !this.buildConfig.release
      // 预留扩展参数
      // exConfig: exConfigObj
    }, buildPkg);
    return compileResult.sopPath;
  }

  /**
   * 编译插件
   */
  private compilePlugins(): void {
    log.verbose('Build compilePlugins()')

    // 查找插件
    const pluginsPath = path.join(this.appPath, 'platforms/syberos/syberh-plugins');
    if (!fs.existsSync(pluginsPath)) {
      log.warn('未找到插件源码目录：', pluginsPath);
      return;
    }
    let plugins = fs.readdirSync(pluginsPath);
    plugins = plugins.filter((f) => {
      const stat = fs.statSync(path.join(pluginsPath, f));
      return stat.isDirectory();
    });

    // 支持s1手机时增加额外参数
    const qmakeArgs: Array<string> = [];
    if (this.buildConfig.s1) {
      qmakeArgs.push('DEFINES+=S1');
    }

    const compiler = new compile.Compiler()
    compiler.buildPlugins({
      // 指向应用中platform/syberos位置
      platformSyberosPath: path.join(this.appPath, 'platforms/syberos'),
      // 编译插件的名称
      plugins: plugins,
      // 应用的sopid
      sopid: this.projectConfig.sopid,
      // 编译输出目录
      buildPath: this.buildDir,
      // pdk命令所在位置
      pdkPath: this.pdkRootPath,
      // target完整名称：target-armv7tnhl-xuanwu
      targetName: this.projectConfig.target,
      // 额外的qmake编译参数
      qmakeArgs: qmakeArgs,
      // 是否使用debug编译
      debug: !this.buildConfig.release
      // 预留扩展参数
      // exConfig: exConfigObj
    });
  }

  /**
   * 安装sop包
   */
  private async installSop(sopPath: string | null) {
    log.verbose('Build installSop()')
    console.log(chalk.green('开始安装sop包...'))

    if (!sopPath || !fs.existsSync(sopPath)) {
      log.error('未找到sop包，停止安装sop包')
      return;
    }

    // 构建完成退出到根目录了，所以这里需要进入到打包目录(.build-*)
    shelljs.cd(this.buildDir)

    // 启动虚拟机
    if (this.useSimulator) {
      console.log(chalk.green('准备启动模拟器'))
      await helper.startvm()
    }

    const cdbSop = new sop.CdbSop(this.pdkRootPath, this.projectConfig.target, this.projectConfig.sopid, this.projectConfig.projectName)
    // 非模拟器，支持cdb
    if (!this.useSimulator && cdbSop.isSupportCdb()) {
      // 发送
      cdbSop.send(sopPath)
      // 安装
      cdbSop.install(path.basename(sopPath))
      // 启动
      cdbSop.startApp()
    } else {
      let ip = this.projectConfig.deployIP
      let port = this.projectConfig.deployPort
      // 使用模拟器时切换模拟器IP、端口
      if(this.useSimulator){
        ip = adapterConfig.simulator.ip
        port = adapterConfig.simulator.port
      }
      const sshSop = new sop.SshSop(ip, port, this.projectConfig.sopid, this.projectConfig.projectName)
      // 发送
      sshSop.send(sopPath)
      // 安装
      sshSop.install(path.basename(sopPath))
      // 启动
      sshSop.startApp()
    }
  }

}
