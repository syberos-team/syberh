"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const path = require("path");
const eslint_1 = require("eslint");
const ESLINT_CONFIG_PATH = path.join(__dirname, 'validatorEslintrc.js');
function default_1({ projectConfig }) {
    const eslintCli = new eslint_1.CLIEngine({
        cwd: process.cwd(),
        useEslintrc: false,
        configFile: ESLINT_CONFIG_PATH
    });
    const sourceFiles = path.join(process.cwd(), projectConfig.sourceRoot, '**/*.{js,ts,jsx,tsx}');
    const report = eslintCli.executeOnFiles([sourceFiles]);
    const formatter = eslintCli.getFormatter();
    return {
        desc: '检查 ESLint (以下为 ESLint 的输出)',
        raw: formatter(report.results)
    };
}
exports.default = default_1;
