import chalk from 'chalk'
import * as path from 'path'
import { log } from '../util/log'
import * as helper from '../syberos/helper'
import * as shelljs from 'shelljs'

export enum InstallType {
  sdk = 'sdk',
  target = 'target'
}

export type InstallOption = {
  // 当前用户密码
  password: string
  // 安装类型
  installType: InstallType
  // sdk安装包的路径，可以使用网络路径
  sdkPath: string
  // target安装包的路径，可以使用网络路径
  targetPath: string
  // 安装路径(若用户没有定义，默认安装路径为~/Syberos-Pdk)
  installPath: string
}



export class Install {
  private option: InstallOption

  constructor(option: InstallOption) {
    this.option = option
  }

  public static installType(type: string): InstallType {
    return InstallType[type]
  }

  public async exec() {
    console.log(chalk.green('准备安装', this.option.installType))
    log.verbose('准备安装：%j', this.option)

    switch (this.option.installType) {
      case InstallType.sdk:
        await this.sdk();
        break;
      case InstallType.target:
        this.target();
        break;
      default:
        console.log(chalk.red('安装类型错误'))
        log.error('安装类型错误: %j', this.option)
        break;
    }
  }


  private async sdk() {
    const cmd = `${helper.locateScripts('PDKInstallManager.sh')} --sudo-password ${this.option.password} --sdk-install-path ${this.option.installPath} --sdk-package ${this.option.sdkPath}`
    log.verbose('安装sdk：%s', cmd)
    shelljs.exec(cmd)
  }

  private target(): void {
    const targetInstallPath = path.join(this.option.installPath, 'targets')
    const cmd = `${helper.locateScripts('PDKInstallManager.sh')} --sudo-password ${this.option.password} --sdk-install-path ${this.option.installPath} --target-install-path ${targetInstallPath} --target-package ${this.option.targetPath}`
    log.verbose('安装target：%s', cmd)
    shelljs.exec(cmd)
  }

  // private targetName(): string {
  //   return path.basename(this.option.targetPath).split('-').slice(0, 3).join('-')
  // }
}