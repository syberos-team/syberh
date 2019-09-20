import chalk from 'chalk'
import * as _ from 'lodash'

import { BUILD_TYPES, DEVICES_TYPES } from './util/constants'
import { IBuildConfig } from './util/types'
import diagnose from './doctor/index'
import * as b from './build/index'
import { getProjectConfig } from './syberos/helper'

export default async function build(appPath, buildConfig: IBuildConfig) {

  if (buildConfig.type) {
    switch (buildConfig.type) {
      case BUILD_TYPES.DEVICE:
        await buildForDevice(appPath, buildConfig)
        break
      case BUILD_TYPES.SIMULATOR:
        await buildForSimulator(appPath, buildConfig)
        break

      default:
        console.log(
          chalk.red('输入类型错误，目前只支持 device(真机)/simulator类型')
        )
    }
  } else {
    // 默认打SOP包
    buildSop(appPath, buildConfig)
  }
}

function buildForDevice(appPath: string, buildConfig: IBuildConfig) {
  require('./build/index').build(appPath, {
    ...buildConfig,
    adapter: BUILD_TYPES.DEVICE
  })
}

function buildForSimulator(appPath: string, buildConfig: IBuildConfig) {
  require('./build/index').build(appPath, {
    ...buildConfig,
    adapter: BUILD_TYPES.SIMULATOR
  })
}

function buildSop(appPath: string, buildConfig: IBuildConfig) {
  require('./build/index').build(appPath, {
    ...buildConfig,
    onlyBuildSop: true
  })
}
