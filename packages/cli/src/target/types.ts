

export enum TargetType {
    ALL = 'all', 
    DEVICE = 'device', 
    SIMULATOR = 'simulator'
}


export interface IAnswer {
    target?: string
    targetSimulator?: string
}

export interface ITargetOption {
    type: TargetType
    // project.config.json 文件路径
    projectConfigPath: string
}