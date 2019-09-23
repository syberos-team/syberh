
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

  constructor(root) {
    this.init()
  }

  init() {
    console.log(chalk.green('开始代码转换...'))
  }
}
