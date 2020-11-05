
export interface ICopyOptions {
  patterns: {
    from: string,
    to: string,
    ignore?: string[]
  }[],
  options: {
    ignore?: string[]
  }
}

export interface ICopyArgOptions {
  filter?: (src: string) => boolean
}

export interface IStatusBar {
    show : boolean,
    style : string
}


// 对应与项目下的 project.config.json文件
export interface IProjectConfig {
  // app id
  projectName: string
  // 应用中文名
  appName: string
  sopid: string
  target: string
  targetSimulator: string
  webPath: string
  // 首页
  homePage: string
  storeBaseUrl: string
  // 手机ip
  deployIP: string
  // 手机端口
  deployPort: string
  // dev服务IP
  devServerIP: string
  // dev服务端口
  devServerPort: string
  // qtwebengine remote debugging 端口
  debuggingPort: string
  // 状态栏相关信息
  statusBar?: IStatusBar
}

// 默认的 project.config.json 内容
export const DEFAULT_PROJECT_CONFIG: IProjectConfig = {
  projectName: '',
  appName: '',
  sopid: '',
  target: '',
  targetSimulator: '',
  webPath: 'www',
  homePage: '',
  storeBaseUrl: 'https://storeinner.syberos.com',
  deployIP: '192.168.100.100',
  deployPort: '22',
  devServerIP: '192.168.100.101',
  devServerPort: '4399',
  debuggingPort: '9867',
  statusBar: {
    show: true,
    style: 'black'
  }
}
