import chalk from 'chalk'
import * as _ from 'lodash'

import { BUILD_TYPES, DEVICES_TYPES } from './util/constants'
import { IBuildConfig } from './util/types'
import diagnose from './doctor/index'
import * as b from './build/index'
import { getProjectConfig } from './syberos/helper'

export default async function build(appPath, webPath, buildConfig: IBuildConfig) {

  if (buildConfig.type) {
    switch (buildConfig.type) {
      case BUILD_TYPES.DEVICE:
        await buildForDevice(appPath, webPath, buildConfig)
        break
      case BUILD_TYPES.SIMULATOR:
        await buildForSimulator(appPath, webPath, buildConfig)
        break

      default:
        console.log(
          chalk.red('输入类型错误，目前只支持 device(真机)/simulator类型')
        )
    }
  } else {
    // 默认打SOP包
    await buildSop(appPath, webPath, buildConfig)
  }
}

async function diagnoseFastfail(buildConfig: IBuildConfig) {
  if (!buildConfig.nodoctor) {
    const hasFail = await diagnose({checkGlobalTarget: false})
    if (hasFail) {
      process.exit(0)
    }
  }
}

async function buildForDevice(appPath: string, webPath: string, buildConfig: IBuildConfig) {
  const projectConfig = getProjectConfig(appPath)
  await diagnoseFastfail(buildConfig)
  await b.build(appPath, webPath, {
    target: projectConfig.target,
    debug: buildConfig.debug,
    adapter: DEVICES_TYPES.DEVICE
  })
}

async function buildForSimulator(appPath: string, webPathh: string, buildConfig: IBuildConfig) {
  const projectConfig = getProjectConfig(appPath)
  await diagnoseFastfail(buildConfig)
  await b.build(appPath, webPathh, {
    target: projectConfig.targetSimulator,
    debug: buildConfig.debug,
    adapter: DEVICES_TYPES.SIMULATOR
  })
}

async function buildSop(appPath: string, webPathh: string, buildConfig: IBuildConfig) {
  const projectConfig = getProjectConfig(appPath)
  await diagnoseFastfail(buildConfig)
  await b.build(appPath, webPathh, {
    target: projectConfig.target,
    debug: buildConfig.debug,
    adapter: DEVICES_TYPES.DEVICE,
    onlyBuildSop: true
  })
}
