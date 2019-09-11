"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const brolog_1 = require("brolog");
const logLevel = process.env.DEV_LOG;
if (logLevel) {
    brolog_1.log.level(logLevel.toLowerCase());
    brolog_1.log.silly('Config', 'LOG set level to %s', logLevel);
}
exports.default = brolog_1.log;
