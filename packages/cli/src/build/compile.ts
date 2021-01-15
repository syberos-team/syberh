import * as fs from 'fs-extra'
import * as path from 'path'
import * as os from 'os'
import * as shelljs from 'shelljs'
import { log } from '../util/log'
import { qtversions } from '../syberos/configfile'
import * as helper from '../syberos/helper'
import chalk from 'chalk'


export interface CompileGeneralConfig {
  // 当前用户的密码
  password?: string
  // 编译输出目录
  buildPath: string
  // Syberos-Pdk所在位置
  pdkPath: string
  // target完整名称：target-armv7tnhl-xuanwu
  targetName: string
  // 额外的qmake编译参数
  qmakeArgs?: Array<string>
  // 并发编译进程数，为空时使用cpu数
  processNum?: number
  // 是否使用debug编译
  debug?: boolean
  // 预留扩展参数
  exConfig?: object
}

export interface CompileConfig extends CompileGeneralConfig {
  // 编译项目的pro文件位置
  proPath: string
}

export interface CompilePluginsConfig extends CompileGeneralConfig {
  // 指向应用中platform/syberos位置
  platformSyberosPath: string
  // 编译插件的名称，会在platform/syberos/syberh-plugins中查找插件
  plugins: Array<string>
  // 应用的sopid
  sopid: string
}

export type CompileResult = {
  sopPath: string | null
}

export class CompileError extends Error {
  constructor(msg: string) {
    super(msg)
    this.name = 'CompileError'
  }
}

export class Compiler {

  /**
   * 编译syberh应用
   */
  public async buildApp(conf: CompileConfig, buildPkg: boolean = true): Promise<CompileResult> {
    log.verbose('buildApp()');

    conf = this.checkAppConfig(conf);

    let result : CompileResult;
    // 检查target是否是5.0版本，若是5.0版本使用不同5.0编译流程
    if(helper.isTargetOS_5(conf.targetName)){
      result = await this.buildByOS5(conf, buildPkg);
    } else{
      result = this.buildByNotOS5(conf, buildPkg);
    }
    return result;
  }

  /**
   * 编译插件
   */
  public buildPlugins(conf: CompilePluginsConfig): void {
    log.verbose('buildPlugins()  conf: %j', conf);

    conf = this.checkPluginConfig(conf);

    if (!conf.qmakeArgs) {
      conf.qmakeArgs = [];
    }
    conf.qmakeArgs.push('SYBERH_APP=' + conf.platformSyberosPath);
    conf.qmakeArgs.push('SOPID=' + conf.sopid);

    // 非5.0版本插件编译
    if(!helper.isTargetOS_5(conf.targetName)){
      this.buildPluginsByNotOS5(conf)
      return
    }

    // 5.0版本插件编译
    for (const pluginName of conf.plugins) {
      let pluginProPath: string;
      try{
        pluginProPath = this.findPluginProPath(pluginName, conf.platformSyberosPath);
      }catch(e){
        if(e instanceof CompileError){
          log.warn('未找到插件编译文件，跳过插件：', pluginName);
        }else{
          log.warn(e.stack)
        }
        continue;
      }
      const compileConfig = this.toCompileConfig(conf, pluginProPath)
      this.buildByOS5(compileConfig, false);
    }
  }


  // 非5.0系统，使用expect脚本编译插件
  private buildPluginsByNotOS5(conf: CompilePluginsConfig) {
    log.verbose('buildPluginsByNotOS5()  conf: %j', conf);

    const pluginProPathes: string[] = []
    for (const pluginName of conf.plugins) {
      let pluginProPath: string;
      try{
        pluginProPath = this.findPluginProPath(pluginName, conf.platformSyberosPath);
        pluginProPathes.push(pluginProPath)
      }catch(e){
        if(e instanceof CompileError){
          log.warn('未找到插件编译文件，跳过插件：', pluginName);
        }else{
          log.warn(e.stack)
        }
        continue;
      }
    }
    log.verbose('plugins pro：', pluginProPathes)

    const proPathes = pluginProPathes.join(',')
    const password = conf.password
    const processNum = conf.processNum ? conf.processNum : 1
    const kchrootPath = path.join(conf.pdkPath, 'sdk/script/kchroot');
    const qmakeArgs = this.composeQmakeArgs(conf);

    if(!password){
      console.log(chalk.redBright('未输入当前用户密码'));
      process.exit(1)
    }
    if(!conf.targetName){
      console.log(chalk.redBright('未设置target'));
      process.exit(1)
    }
    if(!proPathes){
      console.log(chalk.yellow('未找到任何插件编译文件，跳过插件编译'));
      return
    }

    const cmd = `expect ${helper.locateScripts('sb2-build-plugins.sh')} ${password} ${processNum} ${kchrootPath} ${conf.targetName} '${proPathes}' '${qmakeArgs}'`
    log.verbose('执行：', cmd)
    helper.runShell(cmd)
  }


  private buildByNotOS5(conf: CompileConfig, buildPkg: boolean): CompileResult {
    log.verbose('buildByNotOS5()  conf: %j,  buildPkg: %s', conf, buildPkg);

    let sopPath: string | null = null;

    const kchrootPath = path.join(conf.pdkPath, 'sdk/script/kchroot');
    const qmakeArgs = this.composeQmakeArgs(conf);

    const setup1 = `${kchrootPath} 'sb2 -t ${conf.targetName} -R' '/usr/lib/qt5/bin/qmake ${conf.proPath} -r -spec linux-g++ ${qmakeArgs}'`;
    const setup2 = `${kchrootPath} 'sb2 -t ${conf.targetName} -R' '/usr/bin/make -j${conf.processNum}'`;
    const setup3 = `${kchrootPath} 'sb2 -t ${conf.targetName} -R' 'buildpkg ${conf.proPath}'`;

    shelljs.cd(conf.buildPath);
    log.verbose('buildByNotOS5() setup1:', setup1);
    this.shell(setup1);
    log.verbose('buildByNotOS5() setup2:', setup2);
    this.shell(setup2);

    if (buildPkg) {
      log.verbose('buildByNotOS5() setup3:', setup3);
      this.shell(setup3);
      sopPath = this.findSop(conf);
    }

    return {
      sopPath: sopPath
    };
  }

  private async buildByOS5(conf: CompileConfig, buildPkg: boolean): Promise<CompileResult> {
    log.verbose('buildByOS5()  conf: %j,  buildPkg: %s', conf, buildPkg);

    let sopPath: string | null = null;

    const qmakeArgs = this.composeQmakeArgs(conf);
    const qmakePath = await qtversions.getTargetInstallPath(conf.targetName);
    let buildpkg;
    try {
      buildpkg = this.getBuildpkgByOS(qmakePath);
    } catch (e) {
      log.error(e);
      return { sopPath: null };
    }

    const setup1 = `${qmakePath} ${conf.proPath} -r -spec devices/linux-syberos-g++ ${qmakeArgs}`;
    const setup2 = `/usr/bin/make -j${conf.processNum}`;
    const setup3 = `${buildpkg} ${conf.proPath}`;

    shelljs.cd(conf.buildPath);
    log.verbose('buildByOS5() setup1:', setup1);
    this.shell(setup1);
    log.verbose('buildByOS5() setup2:', setup2);
    this.shell(setup2);

    if (buildPkg) {
      log.verbose('buildByOS5() setup3:', setup3);
      this.shell(setup3);
      sopPath = this.findSop(conf);
    }

    return {
      sopPath: sopPath
    };
  }

  /**
   * 判断libpluginmanager.so是否存在
   * @param platformSyberosPath syberh应用中platform/syberos位置
   */
  public existsLib(platformSyberosPath: string): boolean {
    const pluginManagerSoPath = path.join(platformSyberosPath, 'lib/libpluginmanager.so');
    const nativeSdkSoPath = path.join(platformSyberosPath, 'lib/libnativesdk.so');
    log.verbose('existsLib()  pluginmanager: %s,  nativesdk: %s', pluginManagerSoPath, nativeSdkSoPath);
    return fs.existsSync(pluginManagerSoPath) && fs.existsSync(nativeSdkSoPath);
  }

  /**
   * 判断syberh-plugins目录是否存在
   * @param platformSyberosPath syberh应用中platform/syberos位置
   */
  public isSyberhPluginsExists(platformSyberosPath: string): boolean {
    const syberhPluginsPath = path.join(platformSyberosPath, 'syberh-plugins')
    return fs.existsSync(syberhPluginsPath);
  }

  /**
   * 检查应用编译参数，未通过检查时抛出CompileError
   */
  private checkAppConfig(conf: CompileConfig): CompileConfig {
    if (!conf.proPath || !fs.existsSync(conf.proPath)) {
      log.warn('编译项目pro文件不存在：', conf.proPath);
      throw new CompileError('编译项目pro文件不存在');
    }
    return this.checkGeneralConfig(conf);
  }

  /**
   * 检查插件编译配置参数，未通过检查时抛出CompileError
   * @param conf 
   */
  private checkPluginConfig(conf: CompilePluginsConfig): CompilePluginsConfig {
    if (!conf.platformSyberosPath || !fs.existsSync(conf.platformSyberosPath)) {
      log.warn('未找到syberos平台应用目录：', conf.platformSyberosPath);
      throw new CompileError('未找到syberos平台应用目录');
    }
    if (!conf.sopid) {
      log.warn('未指定sopid：', conf.sopid);
      throw new CompileError('未指定sopid件');
    }
    return this.checkGeneralConfig(conf);
  }

  /**
   * 检查共同的编译配置参数，并更新部分参数的默认值，未通过检查时抛出CompileError
   */
  private checkGeneralConfig<T extends CompileGeneralConfig>(conf: T): T {
    if (!conf.buildPath) {
      log.warn('编译输出目录不存在：', conf.buildPath);
      throw new CompileError('编译输出目录不存在');
    }
    if (!fs.existsSync(conf.buildPath)) {
      log.verbose('编译输出目录不存在，创建目录：', conf.buildPath);
      fs.mkdirsSync(conf.buildPath);
    }
    if (!conf.targetName) {
      log.warn('未配置target', conf.targetName);
      throw new CompileError('未配置target');
    }
    // os5时不检查pdk
    if(!helper.isTargetOS_5(conf.targetName)){
      if (!conf.pdkPath || !fs.existsSync(conf.pdkPath)) {
        log.warn('未找到pdk命令：', conf.pdkPath);
        throw new CompileError('未找到pdk命令');
      }
    }
    if (!conf.processNum || conf.processNum <= 0) {
      const cpus = this.cpuNum();
      log.verbose('未配置编译进程数，使用cpu数：', cpus);
      conf.processNum = cpus;
    }
    return conf;
  }

  /**
   * 获取CUP进程数
   */
  private cpuNum() {
    return os.cpus().length
  }

  private toCompileConfig(conf: CompileGeneralConfig, proPath: string): CompileConfig {
    return {
      proPath: proPath,
      buildPath: conf.buildPath,
      pdkPath: conf.pdkPath,
      targetName: conf.targetName,
      qmakeArgs: conf.qmakeArgs,
      processNum: conf.processNum,
      debug: conf.debug,
      exConfig: conf.exConfig
    }
  }

  /**
   * 将conf参数中的exConfig和qmakeArgs组装成功qmake额外的参数字符串
   */
  private composeQmakeArgs<T extends CompileGeneralConfig>(conf: T): string {
    const qmakeArgs: Array<string> = []
    // debug
    if (conf.debug) {
      qmakeArgs.push('CONFIG+=debug CONFIG+=qml_debug')
    } else {
      qmakeArgs.push('CONFIG+=release')
    }
    // EX_CONFIG
    if (conf.exConfig) {
      const exConfig = Buffer.from(JSON.stringify(conf.exConfig), 'utf8').toString('hex');
      qmakeArgs.push('EX_CONFIG=' + exConfig);
    }

    if (conf.qmakeArgs && conf.qmakeArgs.length > 0) {
      qmakeArgs.push(...conf.qmakeArgs)
    }
    if (qmakeArgs.length > 0) {
      return qmakeArgs.join(' ')
    }
    return ''
  }

  /**
   * 查找conf参数中的buildPath路径下的sop文件，未找到时返回null
   * 若存在多个sop文件，则返回更改时间最新的文件
   */
  private findSop<T extends CompileGeneralConfig>(conf: T): string | null {
    log.verbose('findSop()  buildPath:', conf.buildPath);
    const files = fs.readdirSync(conf.buildPath, { encoding: 'utf8' });

    const sopFilePathes: Array<string> = [];
    for (const f of files) {
      if(f.endsWith('.sop')){
        sopFilePathes.push(path.join(conf.buildPath, f));
        continue;
      }
    }
    if(sopFilePathes.length === 0){
      return null;
    }

    let tmpCtime: number = -1;
    let tmpSopPath: string|null = null;
    for(const sopFilePath of sopFilePathes){
      if(!fs.existsSync(sopFilePath)){
        continue;
      }
      const fileCtimeMs = fs.statSync(sopFilePath).ctimeMs;
      if(fileCtimeMs > tmpCtime){
        tmpCtime = fileCtimeMs;
        tmpSopPath = sopFilePath;
      }
    }
    return tmpSopPath;
  }

  /**
   * 组装指定插件中的pro文件路径，并且会检查pro文件是否存在，不存在时抛出CompileError
   */
  private findPluginProPath(pluginName: string, platformSyberosPath: string): string {
    const proPath = path.join(platformSyberosPath, 'syberh-plugins', pluginName, pluginName + '.pro');
    if (!fs.existsSync(proPath)) {
      throw new CompileError('未找到插件' + pluginName);
    }
    return proPath
  }
  /**
   * 执行shell命令
   */
  private shell(cmd: string): void {
    // 关闭控制台输出命令执行结果
    // shelljs.config.silent = true;
    shelljs.exec(cmd);
    // 执行完成后重新打开
    // shelljs.config.silent = false;
  }

  /**
   * 获取buildpkg命令全路径，只适用于os5的target，
   * @param qmakePath os5的target中的qmake路径
   * @throws CompileError 若未找打buildpkg时抛出
   */
  private getBuildpkgByOS(qmakePath : string) : string{
    const buildpkg = path.resolve(qmakePath, '../../../sysroot/usr/bin/buildpkg');
    if(!fs.existsSync(buildpkg)){
      throw new CompileError(`未找到 buildpkg: ${buildpkg}`);
    }
    return buildpkg
  }
}