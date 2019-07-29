import * as path from 'path'

import chalk from 'chalk'






export default class Convertor {
  root: string
  convertRoot: string
  convertDir: string
  importsDir: string
  pages: Set<string>
  hadBeenCopyedFiles: Set<string>
  hadBeenBuiltComponents: Set<string>
  hadBeenBuiltImports: Set<string>
  entryJSPath: string
  entryJSONPath: string
  entryStylePath: string
  entryStyle: string

  constructor (root) {
    this.root = root
    this.convertRoot = path.join(this.root, 'taroConvert')
    this.convertDir = path.join(this.convertRoot, 'src')
    this.importsDir = path.join(this.convertDir, 'imports')
    this.pages = new Set<string>()
    this.hadBeenCopyedFiles = new Set<string>()
    this.hadBeenBuiltComponents = new Set<string>()
    this.hadBeenBuiltImports = new Set<string>()
    this.init()
  }

  init () {
    console.log(chalk.green('开始代码转换...'))
   
  }

}
