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
    await buildSop(appPath, buildConfig)
  }
}

async function diagnoseFastfail(buildConfig: IBuildConfig) {
  if (!buildConfig.nodoctor) {
    const hasFail = await diagnose()
    if (hasFail) {
      process.exit(0)
    }
  }
}

async function buildForDevice(appPath: string, buildConfig: IBuildConfig) {
  const projectConfig = getProjectConfig(appPath)
  await diagnoseFastfail(buildConfig)
  await b.build(appPath, {
    target: projectConfig.target,
    debug: buildConfig.debug,
    adapter: DEVICES_TYPES.DEVICE
  })
}

async function buildForSimulator(appPath: string, buildConfig: IBuildConfig) {
  const projectConfig = getProjectConfig(appPath)
  await diagnoseFastfail(buildConfig)
  await b.build(appPath, {
    target: projectConfig.targetSimulator,
    debug: buildConfig.debug,
    adapter: DEVICES_TYPES.SIMULATOR
  })
}

async function buildSop(appPath: string, buildConfig: IBuildConfig) {
  const projectConfig = getProjectConfig(appPath)
  await diagnoseFastfail(buildConfig)
  await b.build(appPath, {
    target: projectConfig.target,
    debug: buildConfig.debug,
    adapter: DEVICES_TYPES.DEVICE,
    onlyBuildSop: true
  })
}
