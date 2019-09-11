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
const _ = require("lodash/fp");
const npmCheck = require("npm-check");
const isPkgInstalled = _.get('isInstalled');
const isPkgNotInstalled = _.negate(isPkgInstalled);
function checkPkgs({ appPath }) {
    return __awaiter(this, void 0, void 0, function* () {
        let errorLines = [];
        const pkgs = yield npmCheck({
            cwd: appPath
        })
            .then(_.invoke('all'))
            .then(_.get('packages'));
        errorLines = _.concat(errorLines, pkgsNotInstalled(pkgs));
        return {
            desc: '检查依赖',
            lines: errorLines
        };
    });
}
function pkgsNotInstalled(pkgs) {
    const uninstalledPkgs = _.filter(isPkgNotInstalled, pkgs);
    const lines = _.map(pkg => Object({
        desc: `使用到的依赖 ${pkg.moduleName} 还没有安装`,
        valid: false,
        solution: `请安装依赖, yarn add ${pkg.moduleName}`
    }), uninstalledPkgs);
    return lines;
}
exports.default = checkPkgs;
