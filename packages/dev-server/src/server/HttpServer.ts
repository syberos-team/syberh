
import * as express from 'express'
import * as fs from 'fs-extra'
import * as path from 'path'
import * as os from 'os';
import * as bodyParser from 'body-parser'
import ip from 'internal-ip'
import { fileName } from '../util/file';
import log from '../util/log';


// 服务对象
let server: any;
let uri: string
/***
 * http文件下载服务,提供下载服务
 * @param options {port?:number}  
 */
export default class HttpServer {
  // 服务端口
  private port: number;


  constructor(port: number = 0) {
    this.port = port;
    this.start()
  }

  public async  start() {

    if (server) {
      log.verbose('当前服务已存在,不再重新新服务');
      return;
    }

    const app = express()
    app.use(bodyParser.json({ limit: '10000kb' }))
    app.use(bodyParser.urlencoded({ limit: '10000kb', extended: true }))

    app.get('/download', function (req, res) {
      let filePath = req.query.path
      filePath = path.join(path.resolve('.'), filePath)
      
      if (fs.existsSync(filePath)) {
        res.writeHead(200, {
          // 告诉浏览器这是一个二进制文件
          'Content-Type': 'application/octet-stream',
          // 告诉浏览器这是一个需要下载的文件
          'Content-Disposition': 'attachment; filename=' + encodeURI(fileName(filePath))
        })
        // 得到文件输入流
        const readStream = fs.createReadStream(filePath)

        readStream.on('data', (chunk) => {
          // 文档内容以二进制的格式写到response的输出流
          res.write(chunk, 'binary')
        })
        readStream.on('end', () => {
          res.end()
          log.verbose('下载完成', new Date());
        })
      } else {

        res.status(404).send('Sorry, 文件不存在!')
      }
    })



    server = app.listen(this.port, async () => {
      console.log('http Server started.')
      const host = await this.getIP();
      const port = server.address().port;

      uri = `http://${host}:${port}`;
      log.info('http Server started.', uri)
    })
  }

  async getIP() {
    let sip
    const ifaces = os.networkInterfaces()
    Object.keys(ifaces).forEach(function (dev) {
      ifaces[dev].forEach(function (details) {
        if (details.family === 'IPv4') {
          // 优先使用192.168.100.x段ip
          if (details.address.indexOf('192.168.100.10') >= 0) {
            sip = details.address
          }
        }
      })
    })

    if (!sip) {
      sip = await ip.v4()
    }

    return sip
  }
  /**
   * 返回端口
   */
  public getPort() {
    return this.port;
  }

  /**
   * 获取下载服务地址
   */
  public getUri() {
    log.verbose(uri);
    return `${uri}/download`
  }
  public getServer() {
    return server;
  }
}
