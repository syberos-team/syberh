import { IProjectConfig } from '../util/types'
import * as fs from 'fs-extra'
import  { Editor } from 'mem-fs-editor'

// init指令参数
export interface ICreateProjectOption{
    projectDir: string
    projectName?: string
    description?: string
    example?: boolean
    template: string
}

// 项目模板参数
export interface IProjectTemplate extends IProjectConfig{
}


export interface IFile {
    contents: Buffer | NodeJS.ReadableStream | null,
    cwd: string,
    base: string | null | undefined,
    history: string[],
    relative: string,
    dirname: string,
    basename: string,
    stem: string,
    extname: string,
    symlink: string,
    stat: fs.Stats | null
}

export interface IReadOptions {
    raw?: boolean
}

export interface IAppendOptions {
    trimEnd?: boolean,
    separator?: string
}

export interface IMemFsEditor extends Editor{
}

// 创建项目接口
export interface ICreator {
    getFs(): IMemFsEditor
    templatePath (...args: string[]): string
    template (template: string, source: string, dest: string, data?: object, options?): ICreator
}
