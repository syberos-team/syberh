/**
 * FileUtil module. 文件工具类
 * @author lihejia
 */
/**
  * fileName ,获取文件名称
  * @param {string}   filePath文件路径
  * @return {string} fileName  文件名称
  */
export function fileName (filePath: string) {
  const pos = filePath.lastIndexOf('/')
  return filePath.substring(pos + 1)
}
