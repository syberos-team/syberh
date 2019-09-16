import * as fs from 'fs-extra'

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