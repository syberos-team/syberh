"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const path = require("path");
const fs = require("fs-extra");
const util_1 = require("../util");
const constants_1 = require("../util/constants");
function analyzeImportUrl(sourceFilePath, scriptFiles, source, value) {
    const valueExtname = path.extname(value);
    if (path.isAbsolute(value)) {
        util_1.printLog("error" /* ERROR */, '引用文件', `文件 ${sourceFilePath} 中引用 ${value} 是绝对路径！`);
        return;
    }
    if (value.indexOf('.') === 0) {
        if (constants_1.REG_SCRIPT.test(valueExtname) || constants_1.REG_TYPESCRIPT.test(valueExtname)) {
            const vpath = path.resolve(sourceFilePath, '..', value);
            let fPath = value;
            if (fs.existsSync(vpath)) {
                fPath = vpath;
            }
            else {
                util_1.printLog("error" /* ERROR */, '引用文件', `文件 ${sourceFilePath} 中引用 ${value} 不存在！`);
            }
            scriptFiles.add(fPath);
        }
        else {
            let vpath = util_1.resolveScriptPath(path.resolve(sourceFilePath, '..', value));
            if (vpath) {
                if (!fs.existsSync(vpath)) {
                    util_1.printLog("error" /* ERROR */, '引用文件', `文件 ${sourceFilePath} 中引用 ${value} 不存在！`);
                }
                else {
                    if (fs.lstatSync(vpath).isDirectory()) {
                        if (fs.existsSync(path.join(vpath, 'index.js'))) {
                            vpath = path.join(vpath, 'index.js');
                        }
                        else {
                            util_1.printLog("error" /* ERROR */, '引用目录', `文件 ${sourceFilePath} 中引用了目录 ${value}！`);
                            return;
                        }
                    }
                    let relativePath = path.relative(sourceFilePath, vpath);
                    const relativePathExtname = path.extname(relativePath);
                    scriptFiles.add(vpath);
                    relativePath = util_1.promoteRelativePath(relativePath);
                    if (/\.wxs/.test(relativePathExtname)) {
                        relativePath += '.js';
                    }
                    else {
                        relativePath = relativePath.replace(relativePathExtname, '.js');
                    }
                    source.value = relativePath;
                }
            }
        }
    }
}
exports.analyzeImportUrl = analyzeImportUrl;
