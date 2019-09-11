"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const path = require("path");
const fs = require("fs-extra");
const chalk_1 = require("chalk");
const config_1 = require("../config");
const creator_1 = require("./creator");
class Page extends creator_1.default {
    constructor(options) {
        super();
        this.rootPath = this._rootPath;
        this.conf = Object.assign({
            projectDir: '',
            template: '',
            description: ''
        }, options);
    }
    getPkgPath() {
        const projectDir = this.conf.projectDir;
        const pkgPath = path.join(projectDir, 'package.json');
        if (fs.existsSync(pkgPath)) {
            return pkgPath;
        }
        return path.join(projectDir, 'client', 'package.json');
    }
    getTemplateInfo() {
        const pkg = JSON.parse(fs.readFileSync(this.getPkgPath()).toString());
        const templateInfo = pkg.templateInfo || {
            name: 'default',
            css: 'none',
            typescript: false
        };
        templateInfo.template = templateInfo.name;
        delete templateInfo.name;
        this.conf = Object.assign(this.conf, templateInfo);
    }
    create() {
        const date = new Date();
        this.getTemplateInfo();
        this.conf.date = `${date.getFullYear()}-${(date.getMonth() + 1)}-${date.getDate()}`;
        this.write();
    }
    write() {
        const { template, name, typescript, css, projectDir } = this.conf;
        const { createPage } = require(path.join(this.templatePath(), template, 'index.js'));
        createPage(this, {
            page: name,
            projectDir,
            src: config_1.default.SOURCE_DIR,
            template,
            typescript,
            css
        }, () => {
            console.log(`${chalk_1.default.green('✔ ')}${chalk_1.default.grey(`创建页面 ${name} 成功！`)}`);
        });
    }
}
exports.default = Page;
