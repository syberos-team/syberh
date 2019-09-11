import * as chokidar from 'chokidar'
import log from '../util/log'
import { readDirSync } from '../util/file'

/**
 * 文件监控服务
 */
export default class Watcher {
  private server: any
  // 定时器
  private setTimeoutTimer: any
  // 更新的文件列表
  private files: any = []
  // 定时器时长
  private timer: number = 1500
  constructor(server: any, path: any) {
    if (!server) {
      log.error('socket server is undefind')
      throw new Error('socket server is undefind')
    }

    this.server = server
    if (Array.isArray(path)) {
      path.forEach(dirPath => {
        this.watch(dirPath)
      })
    } else if (typeof path === 'string') {
      this.watch(path)
    }
  }

  private addFiles(filePath: string) {
    if (this.files.indexOf(filePath) >= 0) {
    } else {
      this.files.push(filePath)
    }
  }

  private watch(dirPath) {
    const watcher = chokidar.watch(dirPath, {
      ignored: /(^|[/\\])\../,
      persistent: true,
      ignoreInitial: true
    })
    // Add event listeners.
    watcher
      .on('add', path => {
        log.verbose(`File ${path} has been added`)
        this.addFiles(path)
        this.listenerDir(dirPath)
      })
      .on('change', path => {
        log.verbose(`File ${path} has been changed`)
        this.addFiles(path)
        this.listenerDir(dirPath)
      })
      .on('unlink', path => {
        log.verbose(`File ${path} has been removed`)
        const fs = []
        readDirSync(dirPath, fs, fileList => {
          this.files = [...this.files, ...fileList]
          log.verbose('removed files length:', this.files.length)
          this.listenerDir(dirPath)
        })
      })

    // More possible events.
    watcher
      .on('addDir', path => {
        log.verbose(`Directory ${path} has been added`)
        const fs = []
        readDirSync(path, fs, fileList => {
          this.files = [...this.files, ...fileList]
          log.verbose('Directory files length:', this.files.length)
          this.listenerDir(dirPath)
        })
      })
      .on('unlinkDir', path => {
        log.verbose(`Directory ${path} has been removed`)
        const fs = []
        readDirSync(dirPath, fs, fileList => {
          this.files = [...this.files, ...fileList]
          log.verbose('Directory unlinkDir files length:', this.files.length)
          this.listenerDir(dirPath)
        })
      })
      .on('error', error => {
        log.verbose(`Watcher error: ${error}`)
        // listenerDir(wss, dirPath)
      })
      .on('ready', () => {
        log.verbose('Initial scan complete. Ready for changes')
        // listenerDir(wss, dirPath)
      })
      .on('raw', (event, path, details) => {
        // internal
        log.verbose('Raw event info:', event, path, details)
      })
  }

  private listenerDir(path: string) {
    log.verbose('----listenerDir', path)
    // 如果开始了,则删除

    if (this.setTimeoutTimer) {
      log.verbose('清除定时器')
      clearTimeout(this.setTimeoutTimer)
      this.setTimeoutTimer = undefined
    }
    this.setTimeoutTimer = setTimeout(() => {
      log.verbose('setTimeoutTimer', this.setTimeoutTimer)

      this.server.writeFileToClients(this.files, () => {
        this.files = []
      })

      clearTimeout(this.setTimeoutTimer)
      this.setTimeoutTimer = undefined
    }, this.timer)
  }
}
