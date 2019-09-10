import { Brolog, LogLevel } from 'brolog';

class Logger {
  private brolog: Brolog
  private level: LogLevel
  /**
   * 
   * @param logLevel 日志级别字符串，可为空，为空时使用info级别
   */
  constructor(logLevel: string = 'info') {
    this.brolog = Brolog.instance(logLevel.toLowerCase() as any)

    logLevel = logLevel.toLowerCase()
    switch (logLevel) {
      case 'silent':
        this.brolog.level('silent')
        this.level = LogLevel.silent
        break;
      case 'error':
        this.brolog.level('error')
        this.level = LogLevel.error
        break;
      case 'warn':
        this.brolog.level('warn')
        this.level = LogLevel.warn
        break;
      case 'info':
        this.brolog.level('info')
        this.level = LogLevel.info
        break;
      case 'verbose':
        this.brolog.level('verbose')
        this.level = LogLevel.verbose
        break;
      case 'silly':
        this.brolog.level('silly')
        this.level = LogLevel.silly
        break;
      default:
        this.brolog.level('info')
        this.level = LogLevel.info
        break;
    }
  }

  public getLevel(): LogLevel {
    return this.level
  }
  /**
   * 判断是否启用silent级别
   */
  public isSilentEnabled(): boolean {
    return this.level >= LogLevel.silent;
  }
  /**
   * 判断是否启用error级别
   */
  public isErrorEnabled(): boolean {
    return this.level >= LogLevel.error;
  }
  /**
   * 判断是否启用warn级别
   */
  public isWarnEnabled(): boolean {
    return this.level >= LogLevel.warn;
  }
  /**
   * 判断是否启用info级别
   */
  public isInfoEnabled(): boolean {
    return this.level >= LogLevel.info;
  }
  /**
   * 判断是否启用verbose级别
   */
  public isVerboseEnabled(): boolean {
    return this.level >= LogLevel.verbose;
  }
  /**
   * 判断是否启用silly级别
   */
  public isSillyEnabled(): boolean {
    return this.level >= LogLevel.silly;
  }

  public error(prefix: string, ...args: any[]): void {
    this.brolog.error(prefix, ...args)
  }

  public warn(prefix: string, ...args: any[]): void {
    this.brolog.warn(prefix, ...args)
  }

  public info(prefix: string, ...args: any[]): void {
    this.brolog.info(prefix, ...args)
  }

  public verbose(prefix: string, ...args: any[]): void {
    this.brolog.verbose(prefix, ...args)
  }

  public silly(prefix: string, ...args: any[]): void {
    this.brolog.silly(prefix, ...args)
  }
}


export const log = new Logger(process.env.DEV_LOG || '');