"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
function createHash(hashLength = 10) {
    // 默认长度 24
    return Array.from(Array(Number(hashLength) || 24), () => Math.floor(Math.random() * 36).toString(36)).join('');
}
exports.createHash = createHash;
