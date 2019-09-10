import * as net from 'net'
import * as fs from 'fs-extra'
import * as chalk from 'chalk'
import * as uuid from 'uuid'
import ip from 'internal-ip'
import * as os from 'os';
import * as path from 'path';
import HttpServer from './HttpServer';
import log from '../util/log';


/**
 * 文件头信息
 */
interface FileHead {
  // 传送ID,可以通过传输id判断是否重新传输
  uid: number
  server: string
  files: [string]
}

interface ServerConfig {
  host?: string
  port: number
}

enum SendStatus {
  // 等待
  WATING = 0,
  // 发送中
  PENDING = 1,
  RESOLVE = 2
}
/**
 * socket 服务端
 */
export default class Server {
  // 当前服务端
  private server: any

  // uid
  private uid: number = 0

  // 默认配置
  private conf: ServerConfig = {
    port: 8080
  }

  // 发送队列
  private queue: any[] = []

  // 发送状态
  private sendStatus: SendStatus

  private timer: any = null
  // 客户端列表
  private clients: any[] = []

  private httpServer: any;

  constructor(config = {}) {
    this.conf = { ...this.conf, ...config }
    // 设置待发送状态
    this.sendStatus = SendStatus.WATING

    this.startServer();
  }

  /**
   * 启动socket服务
   */
  private startServer() {
    this.server = net.createServer()
    this.server.on('listening', async () => {
      // 初始化ip地址
      const vhost = this.conf.host || (await ip.v4())
      this.conf.host = vhost;
      const ifaces = os.networkInterfaces();
      Object.keys(ifaces).forEach(dev => {
        ifaces[dev].forEach(details => {
          if (details.family === 'IPv4') {
            log.info(chalk.default.green(`socket服务 ${details.address}:${this.conf.port}`))
          }
        });
      });
    })

    this.server.on('connection', () => {
      log.info('客户端链接');
      this.startHttpServer();
    })
    this.server.on('close', () => {
      log.info('syberos-dev-server服务端关闭')
    })
    this.server.listen(this.conf.port)
    // 监听错误信息
    this.server.on('error', e => {
      if (e.code === 'EADDRINUSE') {
        log.error(`${this.conf.port}端口正被使用,请重新设置`);
      }
    })

    this.onConnections();
  }

  private startHttpServer() {
    this.httpServer = new HttpServer();
  }

  /**
   * 保存客户端socket
   * @param socket
   */
  private async saveClient(socket: net.Socket) {
    this.clients.push(socket)
  }

  /**
   * 移除socket
   * @param socket
   */
  private async removeClient(socket) {
    const { sid } = socket
    for (let i = 0; i < this.clients.length; i += 1) {
      if (this.clients[i].sid === sid) {
        this.clients.splice(i, 1)
        break
      }
    }
  }

  onConnections(callback?) {
    this.server.on('connection', (socket: net.Socket) => {
      Object.assign(socket, { sid: uuid() })
      this.saveClient(socket)


      socket.on('close', () => {
        this.removeClient(socket)
        console.log('syberos-dev-server:客户端 连接断开')
      })

      socket.on('end', () => {
        console.log('syberos-dev-server:客户端 end')
      })

      typeof callback === 'function' && callback(socket)
    })
  }

  /**
   * 添加到队列
   * @param filePath
   * @param callback
   */
  private addQueue(filePath: string, callback?: Function) {

    log.verbose('队列等待中   addQueue:', filePath);
    if (this.queue.length > 0) {
      // 清空数组
      this.queue = []
    }
    // 保存队列内容
    this.queue.push({ filePath, callback })
  }

  /**
   * 获取当前待传输内容
   */
  private getQueue() {
    // 删除并返回第一个
    return this.queue.shift()
  }

  /**
   * 发送给所有客户端
   * @param fileList [] 文件列表
   * @param callback
   */
  public async writeFileToClients(fs) {
    log.verbose('Server writeFileToClients() ')
    log.verbose('files', fs.length);
    const fileList: any = [...fs];
    if (fileList.length === 0) {
      log.info('files', JSON.stringify(fileList))
      return;
    }

    if (this.sendStatus === SendStatus.PENDING) {
      // 当前状态发送中，加入队列等待
      this.addQueue(fileList)
      return
    }
    // 设置问发送状态
    this.sendStatus = SendStatus.PENDING
    const filePath = path.resolve('.');
    let count = 0
    const { clients = [] } = this
    const files = fileList;
    const splitFiles: any = [];
    for (let i = 0; i < files.length; i++) {
      const file = files[i];
      const nf = file.replace(filePath, '');
      log.verbose('nf', nf);
      splitFiles.push(nf);
    }
    log.info('----当前客户端数量:', clients.length)
    // console.log('----替换后的地址:', JSON.stringify(splitFiles))
    clients.forEach(async socket => {
      this.uid += 1
      // 获取下载服务地址
      const serverhost = this.httpServer.getUri();
      log.verbose('----serverhost:', serverhost)
      // 发送数据格式
      const fileHead: FileHead = {
        uid: this.uid,
        server: serverhost,
        files: splitFiles

      }
      await this.write(socket, JSON.stringify(fileHead));
      count += 1;
    })

    // 启动定时器扫描发送情况
    this.timer = setInterval(() => {
      if (count === clients.length) {
        log.info('-----发送完成,发送数量', clients.length)
        clearInterval(this.timer)
        this.timer = null
        // 说明已经发送完成，开始检查队列
        this.sendStatus = SendStatus.RESOLVE
        const queue = this.getQueue()
        if (!queue) {
          return
        }
        this.writeFileToClients(queue.filePath)
      }
    }, 1000)
  }

  readDirSync(dirPath, files: any = [], callback) {
    const pa = fs.readdirSync(dirPath);
    const that = this;
    pa.forEach(function (ele, index) {
      const info = fs.statSync(path.join(dirPath, ele));
      if (info.isDirectory()) {
        that.readDirSync(path.join(dirPath, ele), files, null);
      } else {

        const filePath = path.join(dirPath, ele);
        files.push(filePath)
      }
    })

    if (callback) callback(files);
  }

  /**
   * 获取当前链接
   * @param callback 回调方法
   */
  getConnections(callback) {
    this.server.getConnections(callback)
  }

  onEnd(socket, callback) {
    socket.on('end', () => {
      log.warn('connect end')
    })
  }

  onClose(callback) {
    this.server.on('close', () => {
      log.info('onClose')
      callback && callback()
    })
  }

  /**
   * 刷新发送soket数据
   * @param socket
   * @param buffer
   */
  async write(socket: net.Socket, buffer: string) {
    return new Promise(function (resole, reject) {
      socket.write(buffer, function () {
        resole(true)
      })
    })
  }
}
