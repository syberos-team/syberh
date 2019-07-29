import * as fs from 'fs-extra'
import * as shelljs from 'shelljs'
import { createHash } from './hash'

/**
 * 生成压缩文件
 * @param input  文件路径
 * @param output 输入路径
 * @param hash 是否自动hash,默认为true
 *
 */
export async function gzDir(
  input: string,
  output: string,
  hash: boolean = true
) {
  const stat = fs.statSync(input)

  if (!stat.isDirectory) {
    throw new Error('文件非路径格式')
  }
  if (!fs.existsSync(input)) {
    throw new Error('文件路径不存在')
  }

  let hashCode

  // 判断是否增加hash
  if (hash) {
    hashCode = '.' + createHash()
  }

  let outPath: string
  if (output) {
    outPath = output
  } else {
    outPath = `${input}${hashCode}.tar.gz`
  }

  // 进入文件目录
  await shelljs.cd(input)
  // 压缩当前目录下的所有
  const cmd = `tar zcvf ${outPath} *`
  await shelljs.exec(cmd)

  return outPath
}
