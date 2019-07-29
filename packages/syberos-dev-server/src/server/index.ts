import * as net from 'net'
import * as fs from 'fs-extra'
import * as chalk from 'chalk'
import * as uuid from 'uuid'
import ip from 'internal-ip'

/**
 * 发送数据内容
 */
interface FileInfo {
  size: number
  name: string
  data?: string
}

/**
 * 文件头信息
 */
interface FileHead {
  // 传送ID,可以通过传输id判断是否重新传输
  uid: number
  fileInfo: FileInfo
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

  constructor(config = {}) {
    this.conf = { ...this.conf, ...config }
    // 设置待发送状态
    this.sendStatus = SendStatus.WATING
    this.server = net.createServer()
    this.server.on('listening', async () => {
      // 初始化ip地址
      const vhost = this.conf.host || (await ip.v4())

      console.log(`syberos-dev-server 服务监听 ${vhost}:${this.conf.port}`)
    })

    this.server.on('close', () => {
      console.log('syberos-dev-server服务端关闭')
    })
    this.server.listen(this.conf.port)
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

  onConnections(callback) {
    this.server.on('connection', (socket: net.Socket) => {
      Object.assign(socket, { sid: uuid() })
      this.saveClient(socket)

      socket.on('error', e => {
        console.log(`syberos-dev-server:客户端 error: ${e.stack}`)
      })

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
   * 获取文件名称
   * @param filePath {string} 文件路径
   * @return fileName {string} 文件名称
   */
  private fileName(filePath: string) {
    const pos = filePath.lastIndexOf('/')
    return filePath.substring(pos + 1)
  }

  /**
   * 发送文件
   * @param socket
   * @param filePath  文件信息
   * @param callback   发送完成的回调,成功会返回true
   */
  public async writeFile(
    socket: net.Socket,
    fileHead: FileHead,
    filePath: string,
    callback?: Function
  ) {
    if (!socket) {
      throw new Error('socket 不能为空')
    }

    this.uid += 1
    // const hsize=JSON.stringify(obj).length;
    const objString = JSON.stringify(fileHead)
    await this.write(socket, objString)
    // socket.write(objString)
    let sendSize = 0
    const packSize = 1024
    const fd = fs.openSync(filePath, 'r')
    const buf = Buffer.alloc(packSize)
    let countData = 0
    const { name, size } = fileHead.fileInfo
    console.log(chalk.green(`开始发送数据，文件名:${name} ,文件大小:${size}`))
    while (sendSize < fileHead.fileInfo.size) {
      // readSync参数:文件ID,buffer对象,写入buffer的起始位置,写入buffer的结束位置,读取文件的起始位置
      fs.readSync(fd, buf, 0, buf.length, sendSize)
      const data = buf.toString('hex') // 以十六进制传输

      // console.log('buf.length', buf.length)
      socket.write(data)
      sendSize += packSize
      countData += buf.length
    }
    console.log('发送完成', countData)

    callback && callback(true)
  }

  /**
   * 添加到队列
   * @param filePath
   * @param callback
   */
  private addQueue(filePath: string, callback?: Function) {
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
   * @param filePath
   * @param callback
   */
  public async writeFileToClients(filePath: string) {
    if (!fs.existsSync(filePath)) {
      // throw new Error(`文件:${filePath},不存在,请检查`)
      console.error(`文件:${filePath},不存在,请检查`)
      return
    }

    if (this.sendStatus === SendStatus.PENDING) {
      // 当前状态发送中，加入队列等待
      this.addQueue(filePath)
      return
    }
    // 设置问发送状态
    this.sendStatus = SendStatus.PENDING
    const name = this.fileName(filePath)

    const stat = fs.statSync(filePath)
    const { size } = stat

    this.uid += 1
    // 发送数据格式
    const fileHead: FileHead = {
      uid: this.uid,
      fileInfo: {
        size,
        name
      }
    }

    const { clients } = this

    console.log('----当前客户端数量:', clients.length)
    let count = 0
    clients.forEach(socket => {
      this.writeFile(socket, fileHead, filePath, () => {
        console.log('------发送返回')
        count += 1
      })
    })

    // 启动定时器扫描发送情况
    this.timer = setInterval(() => {
      if (count === clients.length) {
        console.log('-----发送完成')
        clearInterval(this.timer)
        this.timer = null
        // 说明已经发送完成，开始检查队列
        this.sendStatus = SendStatus.RESOLVE
        const queue = this.getQueue()
        if (!queue) {
          return
        }
        console.log('------queue', JSON.stringify(queue))
        this.writeFileToClients(queue.filePath)
      }
    }, 1000)
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
      console.log('connect end')
    })
  }

  onClose(callback) {
    this.server.on('close', () => {
      console.log('onClose')
      callback && callback()
    })
  }

  /**
   * 刷新发送soket数据
   * @param socket
   * @param buffer
   */
  async write(socket: net.Socket, buffer: string) {
    return new Promise(function(resole, reject) {
      const r = socket.write(buffer, function(res) {
        console.log('-------async write', res)
        resole(true)
      })
      console.log('----r', r)
    })
  }
}
