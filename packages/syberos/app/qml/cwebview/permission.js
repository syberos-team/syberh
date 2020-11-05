.pragma library

//缓存，存储授权信息
var localPermission = {};

/**
 *  存储授权信息
 * @param {String} securityOrigin
 * @param {String} feature
 */
function setPermission (securityOrigin, feature, action) {
    var permissionStr = securityOrigin.toString() + "#" + feature.toString();
    localPermission[permissionStr] = action;
}
/**
 * 获取当前授权信息
 * @param {*} securityOrigin
 * @param {*} feature
 */
function getPermission (securityOrigin, feature) {
    var permissionStr = securityOrigin.toString() + "#" + feature.toString();
    var action = localPermission[permissionStr];
    return action;
}