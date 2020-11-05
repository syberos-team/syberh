import * as path from 'path'
import * as fs from 'fs-extra'
import * as memFs from 'mem-fs'
import * as editor from 'mem-fs-editor'
import * as _ from 'lodash'
import { IMemFsEditor, ICreator } from './types'
import { getRootPath } from '../util'


export default class Creator implements ICreator {
  private fs: IMemFsEditor

  private _rootPath: string
  private _destinationRoot: string

  constructor () {
    const store = memFs.create()
    this.fs = editor.create(store)
    this.sourceRoot(path.join(getRootPath()))
    this.init()
  }

  init () {}

  sourceRoot (rootPath?: string) {
    if (typeof rootPath === 'string') {
      this._rootPath = path.resolve(rootPath)
    }
    if (!fs.existsSync(this._rootPath)) {
      fs.ensureDirSync(this._rootPath)
    }
    return this._rootPath
  }

  templatePath (...args: string[]): string {
    let filepath = path.join.apply(path, args)
    if (!path.isAbsolute(filepath)) {
      filepath = path.join(this._rootPath, 'templates', filepath)
    }
    return filepath
  }

  destinationRoot (rootPath?: string): string {
    if (typeof rootPath === 'string') {
      this._destinationRoot = path.resolve(rootPath)
      if (!fs.existsSync(rootPath)) {
        fs.ensureDirSync(rootPath)
      }
      process.chdir(rootPath)
    }
    return this._destinationRoot || process.cwd()
  }

  destinationPath (...args: string[]): string {
    let filepath = path.join.apply(path, args)
    if (!path.isAbsolute(filepath)) {
      filepath = path.join(this.destinationRoot(), filepath)
    }
    return filepath
  }

  template (template: string, source: string, dest: string, data?: object, options?) {
    if (typeof dest !== 'string') {
      options = data
      data = dest
      dest = source
    }
    this.fs.copyTpl(
      this.templatePath(template, source),
      this.destinationPath(dest),
      Object.assign({ _ }, this, data),
      options
    )
    return this
  }

  getFs(): IMemFsEditor {
    return this.fs;
  }

  writeGitKeepFile (dirname: string) {
    dirname = path.resolve(dirname)
    fs.writeFileSync(path.join(dirname, '.gitkeep'), 'Place hold file', 'utf8')
  }

  write () {}
}
