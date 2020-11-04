
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
  projectName: string
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
  debuggingPort: string ,
  // 状态栏相关信息
  statusBar : IStatusBar
}
