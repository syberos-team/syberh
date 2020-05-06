const chalk = require('chalk')
const path = require('path')
const shelljs = require('shelljs')
const program = require('commander')
const os = require('os')
const fs = require('fs-extra')

/**
 * 调用示例：
 * node scripts/pluginCompile.js --build /home/abeir/workspace/syberos/build --pdk /home/abeir/Syberos-Pdk \
 * --target target-armv7tnhl-xuanwu --pro /home/abeir/workspace/syberos/syberh-plugins/audio \
 * --qmakeArgs SYBERH_APP=/home/abeir/workspace/syberos/test/example/platforms/syberos,SOPID=com.syberos.example
 */

program
  .option('--build [buildPath]', '编译输出目录')
  .option('--pdk [pdkPath]', 'Syberos-Pdk所在位置')
  .option('--target [targetName]', 'target完整名称：target-armv7tnhl-xuanwu')
  .option('--pro [proPath]', '编译的项目pro文件位置')
  .option('--qmakeArgs [qmakeArgs]', '额外的qmake编译参数', (v) => v.split(','), [])
  .option('--num [processNum]', '并发编译进程数，为空时使用cpu数')
  .option('--debug', '编译debug版本')
  .option('--exConfig [exConfig]', '扩展参数')
  .parse(process.argv)

const qmakePath = '/usr/lib/qt5/bin/qmake'

const compileConfig = {
  // 编译输出目录
  buildPath: program.build,
  // Syberos-Pdk所在位置
  pdkPath: program.pdk,
  // target完整名称：target-armv7tnhl-xuanwu
  targetName: program.target,
  // 编译的项目pro文件位置
  proPath: program.pro,
  // 额外的qmake编译参数
  qmakeArgs: program.qmakeArgs,
  // 并发编译进程数，为空时使用cpu数
  processNum: program.num,
  // 是否编译debug版本
  debug: !!program.debug,
  // 扩展参数（字符串）
  exConfig: program.exConfig
}

class PluginCompiler {
  constructor(conf) {
    this.conf = { ...conf }
  }

  build () {
    this.verbose('PluginCompiler.build()  conf: %j', this.conf)

    const errorMessage = this.checkConf()
    if (errorMessage) {
      console.log(chalk.redBright(errorMessage))
      return
    }

    const currentDir = shelljs.pwd()

    if (!fs.existsSync(this.conf.buildPath)) {
      fs.mkdirsSync(this.conf.buildPath)
    }
    shelljs.cd(this.conf.buildPath)

    const kchrootPath = path.join(this.conf.pdkPath, 'sdk/script/kchroot')
    const qmakeArgs = this.composeQmakeArgs()

    const setup1 = `${kchrootPath} 'sb2 -t ${this.conf.targetName} -R' '${qmakePath} ${this.conf.proPath} -r -spec linux-g++ ${qmakeArgs}'`
    const setup2 = `${kchrootPath} 'sb2 -t ${this.conf.targetName} -R' '/usr/bin/make -j${this.conf.processNum}'`

    shelljs.exec(setup1)
    shelljs.exec(setup2)

    // console.log('============')
    // console.log(this.conf.buildPath)
    // console.log('------------')
    // console.log(setup1)
    // console.log('------------')
    // console.log(setup2)
    // console.log('============')

    shelljs.cd(currentDir)
  }

  composeQmakeArgs () {
    const qmakeArgs = []
    // debug
    if (this.conf.debug) {
      qmakeArgs.push('CONFIG+=qml_debug')
    } else {
      qmakeArgs.push('CONFIG+=release')
    }
    // EX_CONFIG
    if (this.conf.exConfig) {
      qmakeArgs.push('EX_CONFIG=' + this.conf.exConfig)
    }

    if (this.conf.qmakeArgs && this.conf.qmakeArgs.length > 0) {
      qmakeArgs.push(...this.conf.qmakeArgs)
    }
    if (qmakeArgs.length > 0) {
      return qmakeArgs.join(' ')
    }
    return ''
  }

  cpuNum () {
    return os.cpus().length
  }

  verbose (msg, ...args) {
    console.log(msg, ...args)
  }

  checkConf () {
    if (!this.conf) {
      return this.failMessage('编译配置')
    }
    if (!this.conf.buildPath) {
      return this.failMessage('buildPath')
    }
    if (!this.conf.pdkPath) {
      return this.failMessage('pdkPath')
    }
    if (!fs.existsSync(this.conf.pdkPath)) {
      return '未找到Syberos-Pdk所在位置: ' + this.conf.pdkPath
    }
    if (!this.conf.targetName) {
      return this.failMessage('targetName')
    }
    if (!this.conf.proPath) {
      return this.failMessage('proPath')
    }
    if (!fs.existsSync(this.conf.proPath)) {
      return '未找到pro文件: ' + this.conf.proPath
    }
    if (!this.conf.processNum || this.conf.processNum <= 0) {
      this.conf.processNum = this.cpuNum()
    }
    return null
  }

  failMessage (value) {
    return `未设置${value}参数`
  }
}

const compiler = new PluginCompiler(compileConfig)
compiler.build()
