
const fs = require('fs-extra');
const path = require('path');
const pkgJSON = require('../package.json');
const log = require('./log').default;
const shelljs = require('shelljs');

function main () {
  // 定义拷贝的文件或者目录 { name: 'vendor', excludes: ['.git'] }
  const files = [
    { name: 'app' },
    { name: 'tests' },
    { name: 'META-INF' },
    { name: 'app.pro' },
    { name: 'sopconfig.xml' },
    { name: 'syberos.pri' },
    { name: 'VERSION' },
    { name: 'spm.json' }
  ];
  // 获取根目录
  const tempPath = path.resolve('.');

  syncVersion();

  log.verbose('template路径:', tempPath);
  const copyTo = path.resolve('../cli/templates/default/platforms/syberos');
  fs.emptyDirSync(copyTo);
  log.verbose('cli路径:', copyTo);
  for (let nameInfo of files) {
    const src = path.join(tempPath, nameInfo.name);
    copy(src, copyTo, nameInfo.excludes);
  }

  const wwwPath = path.join(copyTo, 'app', 'www');
  log.verbose('cli www:', wwwPath);
  const defaulWWW = path.resolve('../cli/templates/default/www');
  log.verbose('cli defaulWWW:', defaulWWW);
  fs.moveSync(wwwPath, defaulWWW, { overwrite: true });
  log.verbose('cli www move 完成');

  spmInstall(copyTo);

  log.info('template发布完成');
}

function syncVersion () {
  log.verbose('syncVersion()');
  const pkgVersion = pkgJSON.version;
  log.verbose('syncVersion:', pkgVersion);
  const vpath = path.resolve('.', 'VERSION');
  log.verbose('vpath:', vpath);
  const versionConfig = fs.readJSONSync(vpath);
  log.verbose('versionConfig:', versionConfig);
  fs.writeJsonSync(vpath, { version: pkgVersion });
}

function copy (from, to, excludes) {
  const basename = path.basename(from);
  if (fs.existsSync(from)) {
    fs.copySync(from, path.join(to, basename), {
      filter: (src, dest) => {
        if (!excludes || !(excludes instanceof Array)) {
          return true;
        }
        for (const exclude of excludes) {
          if (path.basename(src) === exclude) {
            return false;
          }
        }
        return true;
      }
    });
  }
}

// 使用spm安装依赖
function spmInstall (platformsSyberosDir) {
  process.chdir(platformsSyberosDir);
  const spmInstallCmd = 'spm install';
  log.verbose('执行：%s', spmInstallCmd);
  shelljs.exec(spmInstallCmd);
}

main();
