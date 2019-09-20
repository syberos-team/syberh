import * as path from 'path'
import * as fs from 'fs-extra'
import * as _ from 'lodash/fp'
import targetSdkValidator from './targetSdkValidator'
import syberhValidator from './syberhValidator';
import sdkValidator from './sdkValidator';
import { log } from '../util/log'
import { PROJECT_CONFIG } from '../util/constants'
import chalk from 'chalk';
import * as ora from 'ora'

const validators = {
  validators: [
    targetSdkValidator,
    syberhValidator,
    sdkValidator
  ]
}

// appPath
const appPath = process.cwd()
const NOTE_ALL_RIGHT = chalk.green('[✓] ')
const NOTE_VALID = chalk.yellow('[!] ')
const NOTE_INVALID = chalk.red('[✗] ')
const titleChalk = chalk.hex('#aaa')
const lineChalk = chalk.hex('#fff')
const solutionChalk = chalk.hex('#999')

function printReport(reports) {
  _.forEach(report => {
    console.log('\n' + titleChalk(report.desc))

    if (report.raw) {
      console.log(report.raw)
      return
    }

    if (_.getOr(0, 'lines.length', report) === 0) {
      console.log(`  ${NOTE_ALL_RIGHT}没有发现问题`)
      return
    }

    _.forEach(line => {
      console.log(
        '  ' +
        (line.valid ? NOTE_VALID : NOTE_INVALID) +
        lineChalk(line.desc)
      )
      if (line.solution) {
        console.log('      ' + solutionChalk(line.solution))
      }
    }, report.lines)
  }, reports)
}

export default async function diagnose(): Promise<void> {
  const PROJECT_CONF_PATH = path.join(process.cwd(), PROJECT_CONFIG)

  log.verbose('PROJECT_CONF_PATH:', PROJECT_CONF_PATH)
  if (!fs.existsSync(PROJECT_CONF_PATH)) {
    console.log(chalk.red(`找不到项目配置文件${PROJECT_CONFIG}，请确定当前目录是Syberh项目根目录!`))
    process.exit(1)
  }

  log.verbose('validators:', validators)

  const spinner = ora('正在诊断项目...').start()
  const projectConfig = fs.readJSONSync(PROJECT_CONF_PATH)
  log.verbose('projectConfig', projectConfig)

  const reportsP = _.map(validator => validator({
    appPath,
    projectConfig,
    configPath: PROJECT_CONF_PATH
  }), validators.validators)
  const reports = await Promise.all(reportsP)
  spinner.succeed('诊断完成')
  printReport(reports)
}
