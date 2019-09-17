import * as fs from 'fs-extra'
import * as path from 'path'

/**
 * 读取文件替换文件中的指定内容
 * @param filePath 文件路径
 * @param oldContent 待替换的原内容
 * @param newContent 替换为的新内容
 * @returns 返回新的文件内容
 */
export const replaceFileContent = (filePath: string, oldContent: string, newContent: string): string => {
  const buf = fs.readFileSync(filePath)
  const content = buf.toString().replace(oldContent, newContent)
  fs.writeFileSync(filePath, content)
  return content
}
/**
 * 在当前路径下查找sdk安装包，并获取路径，若当前路径下没有找到sdk安装包则返回空字符串
 */
export const sdkPackagePath = (): string => {
  const pwd = process.cwd()
  const files = fs.readdirSync(pwd)
  if (files) {
    const sdkPaths = files.filter((val): boolean => {
      return val.startsWith('syberos_sdk-') && val.endsWith('.tar.bz2')
    })
    if (sdkPaths && sdkPaths.length > 0) {
      return path.join(pwd, sdkPaths[0])
    }
  }
  return ''
}

/**
 * 在当前路径下查找target安装包，并获取路径，若当前路径下没有target安装包则返回空数组
 */
export const targetPackagePaths = (): string[] => {
  const pwd = process.cwd()
  const files = fs.readdirSync(pwd)
  if (files) {
    return files.map((val): string => {
      if (val.startsWith('target-') && val.endsWith('.tar.bz2')) {
        return path.join(pwd, val)
      }
      return ''
    }).filter((val): boolean => { return val !== '' })
  }
  return []
}