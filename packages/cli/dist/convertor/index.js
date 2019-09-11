"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const path = require("path");
const chalk_1 = require("chalk");
class Convertor {
    constructor(root) {
        this.root = root;
        this.convertRoot = path.join(this.root, 'taroConvert');
        this.convertDir = path.join(this.convertRoot, 'src');
        this.importsDir = path.join(this.convertDir, 'imports');
        this.pages = new Set();
        this.hadBeenCopyedFiles = new Set();
        this.hadBeenBuiltComponents = new Set();
        this.hadBeenBuiltImports = new Set();
        this.init();
    }
    init() {
        console.log(chalk_1.default.green('开始代码转换...'));
    }
}
exports.default = Convertor;
