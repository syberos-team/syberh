const fs = require('fs-extra')
const path = require('path')
const chalk = require('chalk')
const { exec } = require('child_process')
const ora = require('ora')
const {
  TARGET_NAMES,
  TARGET_SIMULATOR_NAMES
} = require('../../dist/util/constants')

const styleExtMap = {
  sass: 'scss',
  less: 'less',
  stylus: 'styl',
  none: 'css'
}

exports.createPage = function (creater, params, cb) {
  const { page, projectDir, src, template, typescript, css } = params
  let pageCSSName
  const sourceDir = path.join(projectDir, src)
  const currentStyleExt = styleExtMap[css] || 'css'

  creater.template(template, 'scss', path.join(sourceDir, 'www', pageCSSName))

  creater.fs.commit(() => {
    if (typeof cb === 'function') {
      cb()
    }
  })
}

exports.createApp = function (creater, params, helper, cb) {
  const {
    projectName,
    projectDir,
    appName,
    template,
    typescript,
    date,
    src,
    css,
    sopid
  } = params
  // syberos app 模块目录
  const platformsDirName = 'platforms'
  // www根目录
  const www = 'ww'
  // APP 模板目录
  const syberosDir = 'syberos'

  // 默认设备target
  const target = TARGET_NAMES['target-armv7tnhl-xuanwu']
  // 默认模拟器target
  const targetSimulator = TARGET_SIMULATOR_NAMES['target-i686-main_dev']

  const libDir = 'lib'
  const projectPath = path.join(projectDir, projectName)
  const sourceDir = path.join(projectPath, src)
  const platformsDir = path.join(projectPath, platformsDirName)
  const version = helper.getPkgVersion()
  const yarnLockfilePath = path.join('yarn-lockfiles', `${version}-yarn.lock`)
  const shouldUseYarn = helper.shouldUseYarn()
  const useNpmrc = shouldUseYarn === false
  const useYarnLock =
    shouldUseYarn &&
    fs.existsSync(creater.templatePath(template, yarnLockfilePath))
  let pageCSSName

  params.page = 'index'
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
    css,
    typescript,
    template
  })

  // 创建project.config.json
  creater.template(
    template,
    'project',
    path.join(projectPath, 'project.config.json'),
    {
      appName,
      projectName,
      sopid,
      target,
      targetSimulator
    }
  )

  // 创建默认git忽略
  creater.template(template, 'gitignore', path.join(projectPath, '.gitignore'))
  creater.template(
    template,
    'editorconfig',
    path.join(projectPath, '.editorconfig')
  )
  creater.template(template, 'eslintrc', path.join(projectPath, '.eslintrc'), {
    typescript
  })

  // 创建index.html
  creater.template(template, 'indexhtml', path.join(sourceDir, 'index.html'))

  switch (css) {
    default:
      appCSSName = 'app.css'
      pageCSSName = 'index.css'
      break
  }
  // 创建 默认 index.css
  creater.template(template, 'scss', path.join(sourceDir, pageCSSName))

  // 创建syberos.pri文件
  creater.template(
    template,
    'syberconfig/syberospri',
    path.join(platformsDir, syberosDir, 'syberos.pri'),
    {
      sopid
    }
  )

  // 创建app.pro文件
  // creater.template(
  //   template,
  //   'syberconfig/apppro',
  //   path.join(platformsDir, syberosDir, 'app', `app.pro`),
  //   {
  //     projectName
  //   }
  // )

  // 创建sopconfig.xml文件
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

  if (useNpmrc) { creater.template(template, 'npmrc', path.join(projectPath, '.npmrc')) }
  if (useYarnLock) {
    creater.template(
      template,
      yarnLockfilePath,
      path.join(projectPath, 'yarn.lock')
    )
  }
  creater.fs.commit(() => {
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
      `${chalk.green('✔ ')}${chalk.grey(`创建www目录: ${projectName}/${src}`)}`
    )

    console.log(
      `${chalk.green('✔ ')}${chalk.grey(
        `拷贝APP模板: ${projectName}/${src}/${platformsDirName}/${syberosDir}`
      )}`
    )

    console.log(
      `${chalk.green('✔ ')}${chalk.grey(
        `创建文件: ${projectName}/${src}/index.html`
      )}`
    )

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
      `${chalk.green('✔ ')}${chalk.grey(`创建文件: ${projectName}/.eslintrc`)}`
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
    const gitInitSpinner = ora(
      `cd ${chalk.cyan.bold(projectName)}, 执行 ${chalk.cyan.bold('git init')}`
    ).start()
    process.chdir(projectPath)
    // git init
    const gitInit = exec('git init')
    gitInit.on('close', code => {
      if (code === 0) {
        gitInitSpinner.color = 'green'
        gitInitSpinner.succeed(gitInit.stdout.read())
      } else {
        gitInitSpinner.color = 'red'
        gitInitSpinner.fail(gitInit.stderr.read())
      }
    })

    // install
    let command
    if (shouldUseYarn) {
      command = 'yarn install'
    } else if (helper.shouldUseCnpm()) {
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
  })
}
