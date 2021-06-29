import { log } from '../util/log'
import * as shelljs from 'shelljs'
import chalk from 'chalk'
import * as path from 'path'
import { isTargetOS_5 } from '../syberos/helper'

const expectScript = {
  // 测试ssh连接
  testSsh(ip: string, port: string): string {
    return `expect<<EOF 
log_user 1
set timeout 1000
spawn ssh -o ConnectTimeout=2 -p ${port} developer@${ip} "pwd"
expect {
  "(yes/no)?" {send "yes\r"; exp_continue}
  "?assword:" {send "system\r"}
}
expect eof
EOF`
  }
}





export class ConnectChecker {
  private pdkRootPath: string
  private targetName: string

  // 记录调用 isSshEnabled 的次数，不允许操过3次
  private callIsSshEnabledNum: number = 0;

  constructor(pdkRootPath: string, targetName: string) {
    this.pdkRootPath = pdkRootPath
    this.targetName = targetName
  }

  isCdbEnabled(): boolean {
    log.verbose('ConnectChecker isCdbEnabled()')
    // os5不检查cdb
    if(isTargetOS_5(this.targetName)){
      return false;
    }
    let result = this.execCdbDevices()
    result = result.toLowerCase()
    return result.indexOf('syber') > 0
  }

  isSshEnabled(ip: string, port: string): boolean {
    log.verbose('ConnectChecker isSshEnabled()')

    this.callIsSshEnabledNum += 1;
    if (this.callIsSshEnabledNum > 3) {
      log.verbose('超过调用isSshEnabled()次数，预期组多3次，实际%s次', this.callIsSshEnabledNum);
      return false;
    }

    // shelljs.config.silent = true
    const result = shelljs.exec(expectScript.testSsh(ip, port))
    // shelljs.config.silent = false
    log.verbose('ssh连接测试结果：\n >> stdout:%s \n >> stderr:%s', result.stdout, result.stderr)

    if (result.stdout.indexOf('RSA host key for 192.168.100.100 has changed') > 0) {
      const userHome = process.env.HOME || process.env.USERPROFILE
      const rmKeyCmd = `ssh-keygen -f "${userHome}/.ssh/known_hosts" -R "192.168.100.100"`;
      log.verbose('删除本地 ssh RSA key：', rmKeyCmd)
      shelljs.exec(rmKeyCmd);
      this.isSshEnabled(ip, port);
    }
    return result.stdout.includes('/data/developer')
  }


  findCdbDevice(): string | undefined {
    log.verbose('ConnectChecker findCdbDevice()')
    const result = this.execCdbDevices()
    const isSupportCdb = result.toLowerCase().includes('-syber')
    if (isSupportCdb) {
      const deviceNames = result.split('\n').map(dev => dev.replace('device', '').trim())
      log.verbose('发现cdb设备：%j', deviceNames)
      const device = deviceNames.filter(dev => dev.toLowerCase().includes('-syber'))[0]
      log.verbose('选中cdb设备：%s', device)
      return device ? device.trim() : undefined
    }
    return undefined
  }

  private execCdbDevices(): string {
    log.verbose('ConnectChecker isCdbEnabled()')
    const cdbPath = this.locateCdb()
    log.verbose('%s devices', cdbPath)

    const cdbCmd = `${cdbPath} devices`
    log.verbose('执行：', cdbCmd)
    // 关闭控制台输出命令执行结果
    shelljs.config.silent = true
    let result = shelljs.exec(`${cdbPath} devices`)
    // 执行完成后重新打开
    shelljs.config.silent = false
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
    return result.stdout || ''
  }


  /**
   * 查找cdb路径
   */
  private locateCdb(): string {
    log.verbose('ConnectChecker locateCdb()')
    return path.join(
      this.pdkRootPath,
      'targets',
      this.targetName,
      'usr/lib/qt5/bin/cdb'
    )
  }

}
