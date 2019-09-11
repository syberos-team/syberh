"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : new P(function (resolve) { resolve(result.value); }).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
const fs = require("fs-extra");
const shelljs = require("shelljs");
const hash_1 = require("./hash");
/**
 * 生成压缩文件
 * @param input  文件路径
 * @param output 输入路径
 * @param hash 是否自动hash,默认为true
 *
 */
function gzDir(input, output, hash = true) {
    return __awaiter(this, void 0, void 0, function* () {
        const stat = fs.statSync(input);
        if (!stat.isDirectory) {
            throw new Error('文件非路径格式');
        }
        if (!fs.existsSync(input)) {
            throw new Error('文件路径不存在');
        }
        let hashCode;
        // 判断是否增加hash
        if (hash) {
            hashCode = '.' + hash_1.createHash();
        }
        let outPath;
        if (output) {
            outPath = output;
        }
        else {
            outPath = `${input}${hashCode}.tar.gz`;
        }
        // 进入文件目录
        yield shelljs.cd(input);
        // 压缩当前目录下的所有
        const cmd = `tar zcvf ${outPath} *`;
        yield shelljs.exec(cmd);
        return outPath;
    });
}
exports.gzDir = gzDir;
