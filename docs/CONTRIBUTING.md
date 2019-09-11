# syberh Contributing Guide

我们非常欢迎社区的开发者向 syberh 做出贡献。在提交贡献之前，请花一些时间阅读以下内容，保证贡献是符合规范并且能帮助到社区。

## Issue 报告指南

如果提交的是 Bug 报告，请务必遵守 [`Bug report`](https://github.com/syberos-team/syberh/blob/master/.github/ISSUE_TEMPLATE/bug_report.md) 模板。

如果提交的是功能需求，请在 issue 的标题的起始处增加 `[Feature request]` 字符。

## 开发配置

你需要保证你的 Node.js 版本大于 8，把仓库 Clone 到本地。运行以下命令：

修改 npm 源

```shell
npm config set registry https://registry.npm.taobao.org
```

本项目使用[Yarn](https://yarn.bootcss.com/)

安装 yarn

```shell
npm install -g yarn
```

本项目使用[lerna](https://github.com/lerna/lerna#readme)

安装 lerna

```shell
npm install lerna -g
```

## 安装依赖

```shell
lerna bootstrap
```

## 启动环境

运行开发环境

```shell
lerna run dev
```

## 提交 commit

整个 syberh 仓库遵从 [Angular Style Commit Message Conventions](https://github.com/angular/angular.js/blob/f3377da6a748007c11fde090890ee58fae4cefa5/CONTRIBUTING.md#commit)，在输入 commit message 的时候请务必遵从此规范。

## 代码风格

- `JavaScript`：JavaScript 风格遵从 [JavaScript Standard Style](https://github.com/standard/standard)。
- `TypeScript`：TypeScript 风格也是 [JavaScript Standard Style](https://github.com/standard/standard) 的变种，详情请看相关包目录下的 `tslint.json` 和 `tsconfig.json`。
- 样式：遵循相关包目录下的 `.stylelintrc` 风格。

## Pull Request 指南

1. 务必保证 `npm run build` 能够编译成功；
2. 务必保证提交到代码遵循相关包中的 `.eslintrc`, `.tslintrc`, `.stylelintrc` 所规定的规范；
3. 当相关包的 `package.json` 含有 `npm test` 命令时，必须保证所有测试用例都需要通过；
4. 当相关包有测试用例时，请给你提交的代码也添加相应的测试用例；
5. 提交代码 commit 时，commit 信息需要遵循 [Angular Style Commit Message Conventions](https://github.com/angular/angular.js/blob/f3377da6a748007c11fde090890ee58fae4cefa5/CONTRIBUTING.md#commit)。
6. 如果提交到代码非常多或功能复杂，可以把 PR 分成几个 commit 一起提交。我们在合并时会会根据情况 squash。

## Credits

感谢以下所有给 syberh 贡献过代码的开发者：

- 感谢 quickhybrid 作者提供了 jsbridge 的实现逻辑和相关代码
- 参与者 <a href="https://github.com/syberos-team/syberh/graphs/contributors">更多</a>
