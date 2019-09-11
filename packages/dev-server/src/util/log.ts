import { log } from 'brolog';

const logLevel = process.env.DEV_LOG
if (logLevel) {
  log.level(logLevel.toLowerCase() as any)
  log.silly('Config', 'LOG set level to %s', logLevel)
}

export default log;