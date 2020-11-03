import { DEVICES_TYPES } from '../util/constants'
import { IProjectConfig } from '../util/types'

// build时的问询结果
export interface BuildAsk {
    // 当前用户密码
    password?: string
}

// build命令参数
export interface BuildConfig {
    // build时的问询信息
    buildAsk?: BuildAsk
    // 真机或模拟器
    type: DEVICES_TYPES
    // 是否检查项目
    doctor?: boolean
    // 只打SOP包，不运行
    onlyBuild?: boolean
    // 支持s1手机
    s1?: boolean
    release: boolean
}

// 编译扩展参数
export interface ExConfig extends IProjectConfig {
    logLevel: string
    debug: boolean
}
