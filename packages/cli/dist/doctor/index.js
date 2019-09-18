"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const pdkSdkValidator_1 = require("./pdkSdkValidator");
const syberhValidator_1 = require("./syberhValidator");
const sdkValidator_1 = require("./sdkValidator");
exports.default = {
    validators: [
        pdkSdkValidator_1.default,
        syberhValidator_1.default,
        sdkValidator_1.default
    ]
};
