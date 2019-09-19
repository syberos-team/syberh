"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const targetSdkValidator_1 = require("./targetSdkValidator");
const syberhValidator_1 = require("./syberhValidator");
const sdkValidator_1 = require("./sdkValidator");
exports.default = {
    validators: [
        targetSdkValidator_1.default,
        syberhValidator_1.default,
        sdkValidator_1.default
    ]
};
