import chalk from 'chalk'
import * as _ from 'lodash'

import { BUILD_TYPES } from './util/constants'
import { IBuildConfig } from './util/types'

export default function build (appPath, buildConfig: IBuildConfig) {
  const { type, debug, port } = buildConfig

  if (type) {
    switch (type) {
      case BUILD_TYPES.DEVICE:
        buildForDevice(appPath, { debug, port })
        break
      case BUILD_TYPES.SIMULATOR:
        buildForSimulator(appPath, { debug })
        break

      default:
        console.log(
          chalk.red('输入类型错误，目前只支持 device(真机)/simulator类型')
        )
    }
  } else {
    // 默认打SOP包
    buildSop(appPath, { debug })
  }
}

function buildForDevice (appPath: string, { debug }: IBuildConfig) {
  require('./build/index').build(appPath, {
    debug,
    adapter: BUILD_TYPES.DEVICE
  })
}

function buildForSimulator (appPath: string, { debug }: IBuildConfig) {
  require('./build/index').build(appPath, {
    debug,
    adapter: BUILD_TYPES.SIMULATOR
  })
}

function buildSop (appPath: string, { debug }: IBuildConfig) {
  require('./build/index').build(appPath, {
    debug,
    onlyBuildSop: true
  })
}
