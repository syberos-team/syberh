import * as fs from 'fs-extra'
import * as path from 'path'
import chalk from 'chalk'
import { exec } from 'child_process'
import * as ora from 'ora'
import { log } from '../util/log'
import * as util from '../util/index'
import { IProjectTemplate, ICreator, ICreateProjectOption } from './types'

// syberh app 模块目录
const platformsDirName = 'platforms'

function getTemplatePath (template = 'default') {
  return path.join(util.getRootPath(), 'templates', template)
}

// 只创建核心项目
export const createCore = function () {
  log.verbose('createCore()')
  // cli 下的核心文件
  const app = path.join(getTemplatePath(), 'platforms', 'syberos', 'app')
  const nativesdk = path.join(getTemplatePath(), 'platforms', 'syberos', 'nativesdk')
  const pluginmanager = path.join(getTemplatePath(), 'platforms', 'syberos', 'pluginmanager')
  const syberhPlugins = path.join(getTemplatePath(), 'platforms', 'syberos', 'syberh-plugins')
  const versionPath = path.join(getTemplatePath(), 'platforms', 'syberos', 'VERSION')
  const jssdkPath = path.join(getTemplatePath(), 'www', 'lib', 'syberh.min.js')
  log.verbose('app path ', app)
  log.verbose('versionConfig', versionPath)
  log.verbose('jssdkPath', jssdkPath)
  // project dir
  const projectDir = path.resolve(process.cwd())
  log.verbose('projectDir path', projectDir)

  const projectSyberosDir = path.join(projectDir, platformsDirName, 'syberos')
  log.verbose('projectSyberosDir path', projectSyberosDir)

  const projectAppDir = path.join(projectSyberosDir, 'app')
  log.verbose('projectAppDir path', projectAppDir)

  const projectVersionPath = path.join(projectDir, platformsDirName, 'syberos', 'VERSION')
  log.verbose('projectVersionPath', projectVersionPath)

  const projecwJSSDK = path.join(projectDir, 'www', 'lib', 'syberh.min.js')
  log.verbose('projecwJSSDK', projecwJSSDK)

  const projectNativesdk = path.join(projectSyberosDir, 'nativesdk')
  log.verbose('projectNativesdk', projectNativesdk)

  const projectPluginmanager = path.join(projectSyberosDir, 'pluginmanager')
  log.verbose('projectPluginmanager', projectPluginmanager)

  const projectSyberhPlugins = path.join(projectSyberosDir, 'syberh-plugins')
  log.verbose('projectSyberhPlugins', projectSyberhPlugins)

  // 删除 app com 目录
  fs.ensureDirSync(projectAppDir)
  log.verbose('removeSync 完成')

  // 重新拷贝app com 目录
  log.verbose('开始拷贝cli app目录')
  fs.copySync(app, projectAppDir)
  log.verbose('拷贝app完成')
  fs.copySync(nativesdk, projectNativesdk)
  log.verbose('拷贝nativesdk完成')
  fs.copySync(pluginmanager, projectPluginmanager)
  log.verbose('拷贝pluginmanager完成')
  fs.copySync(syberhPlugins, projectSyberhPlugins)
  log.verbose('拷贝syberh-plugins完成')
  fs.copySync(versionPath, projectVersionPath)
  log.verbose('拷贝VERSION完成')
  fs.copySync(jssdkPath, projecwJSSDK)
  log.verbose('拷贝JS-SDK完成')
  console.log(
    `${chalk.green('✔ ')}更新 [project] 完成`
  )
}


// 使用模板生成项目
export const createApp = function (creater: ICreator, option: ICreateProjectOption, params: IProjectTemplate, cb?: Function) {
  const { projectDir, template = 'default', example } = option
  const { projectName, appName, sopid } = params

  // APP 模板目录
  const syberosDir = 'syberos'
  const src = 'www'

  const libDir = 'lib'
  const projectPath = path.join(projectDir, projectName)
  const sourceDir = path.join(projectPath, src)
  const platformsDir = path.join(projectPath, platformsDirName)
  const version = util.getPkgVersion()
  const yarnLockfilePath = path.join('yarn-lockfiles', `${version}-yarn.lock`)
  const shouldUseYarn = util.shouldUseYarn()
  const useNpmrc = shouldUseYarn === false
  const useYarnLock =
    shouldUseYarn &&
    fs.existsSync(creater.templatePath(template, yarnLockfilePath))

  fs.ensureDirSync(projectPath)
  fs.ensureDirSync(sourceDir)
  fs.ensureDirSync(path.join(sourceDir, 'lib'))
  fs.ensureDirSync(platformsDir)

  // 拷贝APP模板工程
  fs.copySync(
    path.join(creater.templatePath(), template, platformsDirName),
    platformsDir
  )

  // 拷贝Lib模板工程
  fs.copySync(
    path.join(creater.templatePath(), template, libDir),
    path.join(sourceDir, 'lib')
  )

  // 创建package.json
  creater.template(template, 'pkg', path.join(projectPath, 'package.json'), {
    description: appName,
    projectName,
    version,
    template
  })

  // 创建project.config.json
  fs.writeJSONSync(path.join(projectPath, 'project.config.json'), params, {
    encoding: 'utf-8',
    spaces: '\t',
    EOL: '\n'
  })

  // 创建默认git忽略
  creater.template(template, 'gitignore', path.join(projectPath, '.gitignore'))
  creater.template(
    template,
    'editorconfig',
    path.join(projectPath, '.editorconfig')
  )

  // 是否创建demo项目
  if (example) {
    fs.copySync(
      path.join(creater.templatePath(), template, 'www'),
      path.join(sourceDir)
    )
  } else {
    // 创建index.html
    creater.template(template, 'indexhtml', path.join(sourceDir, 'index.html'))
  }

  // 创建syberos.pri文件
  creater.template(
    template,
    'syberconfig/syberospri',
    path.join(platformsDir, syberosDir, 'syberos.pri'),
    {
      sopid
    }
  )

  creater.template(
    template,
    'syberconfig/sopconfigxml',
    path.join(platformsDir, syberosDir, `sopconfig.xml`),
    {
      appName,
      projectName,
      sopid
    }
  )

  if (useNpmrc) {
    creater.template(template, 'npmrc', path.join(projectPath, '.npmrc'))
  }
  if (useYarnLock) {
    creater.template(
      template,
      yarnLockfilePath,
      path.join(projectPath, 'yarn.lock')
    )
  }
  creater.getFs().commit(() => {
    console.log(
      `${chalk.green('✔ ')}${chalk.grey(
        `创建项目: ${chalk.grey.bold(projectName)}`
      )}`
    )
    console.log(
      `${chalk.green('✔ ')}${chalk.grey(
        `创建模板目录: ${projectName}/${platformsDirName}`
      )}`
    )

    console.log(
      `${chalk.green('✔ ')}${chalk.grey(
        `拷贝APP模板: ${projectName}/${platformsDirName}/${syberosDir}`
      )}`
    )

    console.log(
      `${chalk.green('✔ ')}${chalk.grey(`创建www目录: ${projectName}/${src}`)}`
    )

    // 是否创建demo项目
    if (example) {
      console.log(
        `${chalk.green('✔ ')}${chalk.grey(
          `创建 example: ${projectName}/${src}`
        )}`
      )
    } else {
      console.log(
        `${chalk.green('✔ ')}${chalk.grey(
          `创建文件: ${projectName}/${src}/index.html`
        )}`
      )
    }

    console.log(
      `${chalk.green('✔ ')}${chalk.grey(
        `创建文件: ${projectName}/.editorconfig`
      )}`
    )
    console.log(
      `${chalk.green('✔ ')}${chalk.grey(`创建文件: ${projectName}/.gitignore`)}`
    )
    console.log(
      `${chalk.green('✔ ')}${chalk.grey(
        `创建文件: ${projectName}/package.json`
      )}`
    )
    console.log(
      `${chalk.green('✔ ')}${chalk.grey(
        `创建文件: ${projectName}/project.config.json`
      )}`
    )
    if (useNpmrc) {
      console.log(
        `${chalk.green('✔ ')}${chalk.grey(`创建文件: ${projectName}/.npmrc`)}`
      )
    }
    if (useYarnLock) {
      console.log(
        `${chalk.green('✔ ')}${chalk.grey(
          `创建文件: ${projectName}/yarn.lock`
        )}`
      )
    }
    console.log()

    // git init
    gitInit(projectName, projectPath, () => {
      // install
      npmInstall(shouldUseYarn, projectName, cb)
    })
  })
}

function gitInit (projectName: string, projectPath: string, next?: Function) {
  const gitInitSpinner = ora(
    `cd ${chalk.cyan.bold(projectName)}, 执行 ${chalk.cyan.bold('git init')}`
  ).start()
  process.chdir(projectPath)

  const cmd = exec('git init')
  cmd.on('close', code => {
    if (code === 0) {
      gitInitSpinner.color = 'green'
      gitInitSpinner.succeed(cmd.stdout?.read())
      if (typeof next === 'function') {
        next()
      }
    } else {
      gitInitSpinner.color = 'red'
      gitInitSpinner.fail(cmd.stderr?.read())
    }
  })
}

function npmInstall (shouldUseYarn: boolean, projectName: string, cb?: Function) {
  // install
  let command
  if (shouldUseYarn) {
    command = 'yarn'
  } else if (util.shouldUseCnpm()) {
    command = 'cnpm install'
  } else {
    command = 'npm install'
  }
  const installSpinner = ora(
    `执行安装项目依赖 ${chalk.cyan.bold(command)}, 需要一会儿...`
  ).start()
  exec(command, (error, stdout, stderr) => {
    if (error) {
      installSpinner.color = 'red'
      installSpinner.fail(chalk.red('安装项目依赖失败，请自行重新安装！'))
      console.log(error)
    } else {
      installSpinner.color = 'green'
      installSpinner.succeed('安装成功')
      console.log(`${stderr}${stdout}`)
    }
    console.log(
      chalk.green(`创建项目 ${chalk.green.bold(projectName)} 成功！`)
    )
    console.log(
      chalk.green(
        `请进入项目目录 ${chalk.green.bold(projectName)} 开始工作吧！😝`
      )
    )
    if (typeof cb === 'function') {
      cb()
    }
  })
}
