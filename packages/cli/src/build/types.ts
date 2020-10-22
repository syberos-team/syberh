import { DEVICES_TYPES } from '../util/constants'
import { IProjectConfig } from '../util/types'

// build命令参数
export interface BuildConfig {
    /**
     * 适配器
     */
    type: DEVICES_TYPES
    nodoctor?: boolean,
    // 只打SOP包，不运行
    onlyBuild?: boolean
    // 支持s1手机
    s1?: boolean
    debug: boolean
}

export interface ExConfig extends IProjectConfig {
    logLevel: string
    debug: boolean
}
