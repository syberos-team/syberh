"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
/**
 * FileUtil module. 文件工具类
 * @author lihejia
 */
const fs = require("fs-extra");
const path = require("path");
/**
 * 获取文件名称
 * @param {string}  filePath  -  文件路径
 * @return {string} fileName  文件名称
 */
function fileName(filePath) {
    const pos = filePath.lastIndexOf('/');
    return filePath.substring(pos + 1);
}
exports.fileName = fileName;
/**
 * 读取文件夹下的所有文件
 * @param dirPath  文件夹路径
 * @param files
 * @param callback [files]
 */
function readDirSync(dirPath, files = [], callback) {
    const pa = fs.readdirSync(dirPath);
    const that = this;
    pa.forEach(function (ele, index) {
        const info = fs.statSync(path.join(dirPath, ele));
        if (info.isDirectory()) {
            that.readDirSync(path.join(dirPath, ele), files, null);
        }
        else {
            const filePath = path.join(dirPath, ele);
            if (!(files.indexOf(filePath) >= 0)) {
                files.push(filePath);
            }
        }
    });
    if (callback)
        callback(files);
}
exports.readDirSync = readDirSync;
