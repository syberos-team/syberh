"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const chalk_1 = require("chalk");
class Convertor {
    constructor(root) {
        this.init();
    }
    init() {
        console.log(chalk_1.default.green('开始代码转换...'));
    }
}
exports.default = Convertor;
