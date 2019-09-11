/**
 * FileUtil module. 文件工具类
 * @author lihejia
 */
import * as fs from 'fs-extra'
import * as path from 'path'

/**
  * fileName ,获取文件名称
  * @param {string}   filePath文件路径
  * @return {string} fileName  文件名称
  */
export function fileName (filePath: string) {
  const pos = filePath.lastIndexOf('/')
  return filePath.substring(pos + 1)
}
/**
 * 读取文件夹下的所有文件
 * @param dirPath  文件夹路径
 * @param files
 * @param callback [files]
 */
export function readDirSync (dirPath, files: any = [], callback) {
  const pa = fs.readdirSync(dirPath)
  const that = this
  pa.forEach(function (ele, index) {
    const info = fs.statSync(path.join(dirPath, ele))
    if (info.isDirectory()) {
      that.readDirSync(path.join(dirPath, ele), files, null)
    } else {
      const filePath = path.join(dirPath, ele)
      if (!(files.indexOf(filePath) >= 0)) {
        files.push(filePath)
      }
    }
  })

  if (callback) callback(files)
}
