"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const pdkSdkValidator_1 = require("./pdkSdkValidator");
const packageValidator_1 = require("./packageValidator");
exports.default = {
    validators: [
        pdkSdkValidator_1.default,
        // configValidator,
        packageValidator_1.default
        // recommandValidator,
        // eslintValidator
    ]
};
