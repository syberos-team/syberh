"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const os = require("os");
const chalk_1 = require("chalk");
var processTypeEnum;
(function (processTypeEnum) {
    processTypeEnum["START"] = "start";
    processTypeEnum["CREATE"] = "create";
    processTypeEnum["COMPILE"] = "compile";
    processTypeEnum["CONVERT"] = "convert";
    processTypeEnum["COPY"] = "copy";
    processTypeEnum["GENERATE"] = "generate";
    processTypeEnum["MODIFY"] = "modify";
    processTypeEnum["ERROR"] = "error";
    processTypeEnum["WARNING"] = "warning";
    processTypeEnum["UNLINK"] = "unlink";
    processTypeEnum["REFERENCE"] = "reference";
})(processTypeEnum = exports.processTypeEnum || (exports.processTypeEnum = {}));
exports.processTypeMap = {
    ["create" /* CREATE */]: {
        name: '创建',
        color: 'cyan'
    },
    ["compile" /* COMPILE */]: {
        name: '编译',
        color: 'green'
    },
    ["convert" /* CONVERT */]: {
        name: '转换',
        color: chalk_1.default.rgb(255, 136, 0)
    },
    ["copy" /* COPY */]: {
        name: '拷贝',
        color: 'magenta'
    },
    ["generate" /* GENERATE */]: {
        name: '生成',
        color: 'blue'
    },
    ["modify" /* MODIFY */]: {
        name: '修改',
        color: 'yellow'
    },
    ["error" /* ERROR */]: {
        name: '错误',
        color: 'red'
    },
    ["warning" /* WARNING */]: {
        name: '警告',
        color: 'yellow'
    },
    ["unlink" /* UNLINK */]: {
        name: '删除',
        color: 'magenta'
    },
    ["start" /* START */]: {
        name: '启动',
        color: 'green'
    },
    ["reference" /* REFERENCE */]: {
        name: '引用',
        color: 'blue'
    }
};
exports.CSS_EXT = [
    '.css',
    '.scss',
    '.sass',
    '.less',
    '.styl',
    '.wxss',
    '.acss'
];
exports.SCSS_EXT = ['.scss'];
exports.JS_EXT = ['.js', '.jsx'];
exports.TS_EXT = ['.ts', '.tsx'];
exports.REG_JS = /\.js(\?.*)?$/;
exports.REG_SCRIPT = /\.(js|jsx)(\?.*)?$/;
exports.REG_TYPESCRIPT = /\.(tsx|ts)(\?.*)?$/;
exports.REG_SCRIPTS = /\.[tj]sx?$/i;
exports.REG_STYLE = /\.(css|scss|sass|less|styl|wxss)(\?.*)?$/;
exports.REG_MEDIA = /\.(mp4|webm|ogg|mp3|wav|flac|aac)(\?.*)?$/;
exports.REG_IMAGE = /\.(png|jpe?g|gif|bpm|svg|webp)(\?.*)?$/;
exports.REG_FONT = /\.(woff2?|eot|ttf|otf)(\?.*)?$/;
exports.REG_JSON = /\.json(\?.*)?$/;
exports.REG_WXML_IMPORT = /<import(.*)?src=(?:(?:'([^']*)')|(?:"([^"]*)"))/gi;
exports.REG_URL = /^(?:(?:(?:https?|ftp):)?\/\/)(?:\S+(?::\S*)?@)?(?:(?!(?:10|127)(?:\.\d{1,3}){3})(?!(?:169\.254|192\.168)(?:\.\d{1,3}){2})(?!172\.(?:1[6-9]|2\d|3[0-1])(?:\.\d{1,3}){2})(?:[1-9]\d?|1\d\d|2[01]\d|22[0-3])(?:\.(?:1?\d{1,2}|2[0-4]\d|25[0-5])){2}(?:\.(?:[1-9]\d?|1\d\d|2[0-4]\d|25[0-4]))|(?:(?:[a-z\u00a1-\uffff0-9]-*)*[a-z\u00a1-\uffff0-9]+)(?:\.(?:[a-z\u00a1-\uffff0-9]-*)*[a-z\u00a1-\uffff0-9]+)*(?:\.(?:[a-z\u00a1-\uffff]{2,}))\.?)(?::\d{2,5})?(?:[/?#]\S*)?$/i;
exports.CSS_IMPORT_REG = /@import (["'])(.+?)\1;/g;
exports.NODE_MODULES = 'node_modules';
exports.NODE_MODULES_REG = /(.*)node_modules/;
var BUILD_TYPES;
(function (BUILD_TYPES) {
    BUILD_TYPES["DEVICE"] = "device";
    BUILD_TYPES["SIMULATOR"] = "simulator";
})(BUILD_TYPES = exports.BUILD_TYPES || (exports.BUILD_TYPES = {}));
/**
 * 支持的设备
 */
exports.DEVICES = {
    device: 'device',
    simulator: 'simulator'
};
/**
 * 设备类型
 */
var DEVICES_TYPES;
(function (DEVICES_TYPES) {
    DEVICES_TYPES["DEVICE"] = "device";
    DEVICES_TYPES["SIMULATOR"] = "simulator";
})(DEVICES_TYPES = exports.DEVICES_TYPES || (exports.DEVICES_TYPES = {}));
/**
 * 模拟器target name
 */
exports.TARGET_SIMULATOR_NAMES = {
    'target-i686-xuanwu': 'target-i686-xuanwu',
    'target-i686-main_dev': 'target-i686-main_dev',
    'target-i686-os2_1': 'target-i686-os2_1'
};
/**
 * 真机target name
 */
exports.TARGET_NAMES = {
    'target-armv7tnhl-xuanwu': 'target-armv7tnhl-xuanwu',
    'target-armv7tnhl-xuanwu_singleos_sc9860': 'target-armv7tnhl-xuanwu_singleos_sc9860',
    'target-armv7tnhl-os4_0': 'target-armv7tnhl-os4_0',
    'target-armv7tnhl-os_2_1_lts': 'target-armv7tnhl-os_2_1_lts'
};
/**
 * 模拟器target name
 */
var TARGET_SIMULATOR_NAME_TYPES;
(function (TARGET_SIMULATOR_NAME_TYPES) {
    TARGET_SIMULATOR_NAME_TYPES["target-i686-xuanwu"] = "target-i686-xuanwu";
    TARGET_SIMULATOR_NAME_TYPES["target-i686-main_dev"] = "target-i686-main_dev";
    TARGET_SIMULATOR_NAME_TYPES["target-i686-os2_1"] = "target-i686-os2_1";
})(TARGET_SIMULATOR_NAME_TYPES = exports.TARGET_SIMULATOR_NAME_TYPES || (exports.TARGET_SIMULATOR_NAME_TYPES = {}));
/**
 * 真机target name
 */
var TARGET_NAME_TYPES;
(function (TARGET_NAME_TYPES) {
    TARGET_NAME_TYPES["target-armv7tnhl-xuanwu"] = "target-armv7tnhl-xuanwu";
    TARGET_NAME_TYPES["target-armv7tnhl-xuanwu_singleos_sc9860"] = "target-armv7tnhl-xuanwu_singleos_sc9860";
    TARGET_NAME_TYPES["target-armv7tnhl-os4_0"] = "target-armv7tnhl-os4_0";
    TARGET_NAME_TYPES["target-armv7tnhl-os_2_1_lts"] = "target-armv7tnhl-os_2_1_lts";
})(TARGET_NAME_TYPES = exports.TARGET_NAME_TYPES || (exports.TARGET_NAME_TYPES = {}));
var TEMPLATE_TYPES;
(function (TEMPLATE_TYPES) {
    TEMPLATE_TYPES["WEAPP"] = ".wxml";
    TEMPLATE_TYPES["SWAN"] = ".swan";
    TEMPLATE_TYPES["ALIPAY"] = ".axml";
    TEMPLATE_TYPES["TT"] = ".ttml";
    TEMPLATE_TYPES["QUICKAPP"] = ".ux";
    TEMPLATE_TYPES["QQ"] = ".qml";
})(TEMPLATE_TYPES = exports.TEMPLATE_TYPES || (exports.TEMPLATE_TYPES = {}));
var STYLE_TYPES;
(function (STYLE_TYPES) {
    STYLE_TYPES["WEAPP"] = ".wxss";
    STYLE_TYPES["SWAN"] = ".css";
    STYLE_TYPES["ALIPAY"] = ".acss";
    STYLE_TYPES["TT"] = ".ttss";
    STYLE_TYPES["QUICKAPP"] = ".css";
    STYLE_TYPES["QQ"] = ".qss";
})(STYLE_TYPES = exports.STYLE_TYPES || (exports.STYLE_TYPES = {}));
var SCRIPT_TYPES;
(function (SCRIPT_TYPES) {
    SCRIPT_TYPES["WEAPP"] = ".js";
    SCRIPT_TYPES["SWAN"] = ".js";
    SCRIPT_TYPES["ALIPAY"] = ".js";
    SCRIPT_TYPES["TT"] = ".js";
    SCRIPT_TYPES["QUICKAPP"] = ".js";
    SCRIPT_TYPES["QQ"] = ".js";
})(SCRIPT_TYPES = exports.SCRIPT_TYPES || (exports.SCRIPT_TYPES = {}));
var CONFIG_TYPES;
(function (CONFIG_TYPES) {
    CONFIG_TYPES["WEAPP"] = ".json";
    CONFIG_TYPES["SWAN"] = ".json";
    CONFIG_TYPES["ALIPAY"] = ".json";
    CONFIG_TYPES["TT"] = ".json";
    CONFIG_TYPES["QUICKAPP"] = ".json";
    CONFIG_TYPES["QQ"] = ".json";
})(CONFIG_TYPES = exports.CONFIG_TYPES || (exports.CONFIG_TYPES = {}));
exports.MINI_APP_FILES = {
    ["device" /* DEVICE */]: {
        TEMPL: ".wxml" /* WEAPP */,
        STYLE: ".wxss" /* WEAPP */,
        SCRIPT: ".js" /* WEAPP */,
        CONFIG: ".json" /* WEAPP */
    },
    ["simulator" /* SIMULATOR */]: {
        TEMPL: ".swan" /* SWAN */,
        STYLE: ".css" /* SWAN */,
        SCRIPT: ".js" /* SWAN */,
        CONFIG: ".json" /* SWAN */
    }
};
exports.CONFIG_MAP = {
    ["device" /* DEVICE */]: {
        navigationBarTitleText: 'navigationBarTitleText',
        navigationBarBackgroundColor: 'navigationBarBackgroundColor',
        enablePullDownRefresh: 'enablePullDownRefresh',
        list: 'list',
        text: 'text',
        iconPath: 'iconPath',
        selectedIconPath: 'selectedIconPath',
        color: 'color'
    },
    ["simulator" /* SIMULATOR */]: {
        navigationBarTitleText: 'navigationBarTitleText',
        navigationBarBackgroundColor: 'navigationBarBackgroundColor',
        enablePullDownRefresh: 'enablePullDownRefresh',
        list: 'list',
        text: 'text',
        iconPath: 'iconPath',
        selectedIconPath: 'selectedIconPath',
        color: 'color'
    }
};
// 项目配置文件
exports.PROJECT_CONFIG = 'project.config.json';
exports.DEVICE_RATIO = {
    '640': 2.34 / 2,
    '750': 1,
    '828': 1.81 / 2
};
exports.FILE_PROCESSOR_MAP = {
    '.js': 'babel',
    '.scss': 'sass',
    '.sass': 'sass',
    '.less': 'less',
    '.styl': 'stylus'
};
exports.UPDATE_PACKAGE_LIST = [
    '@tarojs/taro',
    '@tarojs/async-await',
    '@tarojs/cli',
    '@tarojs/components',
    '@tarojs/components-rn',
    '@tarojs/components-qa',
    '@tarojs/taro-h5',
    '@tarojs/taro-tt',
    '@tarojs/taro-quickapp',
    '@tarojs/taro-swan',
    '@tarojs/taro-alipay',
    '@tarojs/plugin-babel',
    '@tarojs/plugin-csso',
    '@tarojs/plugin-sass',
    '@tarojs/plugin-less',
    '@tarojs/plugin-stylus',
    '@tarojs/plugin-uglifyjs',
    '@tarojs/redux',
    '@tarojs/redux-h5',
    '@tarojs/taro-redux-rn',
    '@tarojs/taro-router-rn',
    '@tarojs/taro-rn',
    '@tarojs/rn-runner',
    '@tarojs/router',
    '@tarojs/taro-weapp',
    '@tarojs/webpack-runner',
    'postcss-plugin-constparse',
    'eslint-config-taro',
    'eslint-plugin-taro',
    'taro-transformer-wx',
    'postcss-pxtransform',
    'babel-plugin-transform-jsx-to-stylesheet',
    '@tarojs/mobx',
    '@tarojs/mobx-h5',
    '@tarojs/mobx-rn',
    '@tarojs/mobx-common',
    '@tarojs/mobx-prop-types',
    'nervjs',
    'nerv-devtools'
];
var PARSE_AST_TYPE;
(function (PARSE_AST_TYPE) {
    PARSE_AST_TYPE["ENTRY"] = "ENTRY";
    PARSE_AST_TYPE["PAGE"] = "PAGE";
    PARSE_AST_TYPE["COMPONENT"] = "COMPONENT";
    PARSE_AST_TYPE["NORMAL"] = "NORMAL";
})(PARSE_AST_TYPE = exports.PARSE_AST_TYPE || (exports.PARSE_AST_TYPE = {}));
exports.taroJsComponents = '@tarojs/components';
exports.taroJsQuickAppComponents = '@tarojs/components-qa';
exports.taroJsFramework = '@tarojs/taro';
exports.taroJsRedux = '@tarojs/redux';
exports.DEVICE_RATIO_NAME = 'deviceRatio';
exports.isWindows = os.platform() === 'win32';
