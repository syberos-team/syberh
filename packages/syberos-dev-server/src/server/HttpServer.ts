
import * as express from 'express'
import * as fs from 'fs-extra'
import * as bodyParser from 'body-parser'
import * as path from 'path'

const app = express()
let server
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
      console.log('下载完成 ' + (new Date()))
    })
  } else {
    res.status(404).send('Sorry, 文件不存在!')
  }
})

export const startServer = (port = 20001) => {
  server = app.listen(port, function () {
    console.log('http Server started.')
  })
}

/**
  * 获取文件名称
  * @param filePath {string} 文件路径
  * @return fileName {string} 文件名称
  */
export function fileName (filePath: string) {
  const pos = filePath.lastIndexOf('/')
  return filePath.substring(pos + 1)
}
export const getServer = () => {
  return server
}
