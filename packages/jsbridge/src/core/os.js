/**
 * 加入系统判断功能
 */
export default function osMixin(hybrid) {
    const hybridJs = hybrid;
    const detect = function detect(ua) {
        this.os = {};

        const syberos = ua.match(/(SyberOS);?[\s/]+([\w.]+)?[\s/]+([\w.]+)?/);

        if (syberos) {
            this.os.syberos = true;
            this.os.version = syberos[2];
            this.os.qtVersion = syberos[3];
            // 判断是否为老版本syberos
            this.os.isBadSyberos = !(/Chrome\/\d/.test(window.navigator.appVersion));
        }
        // 如果不是SyberOS，则默认为h5
        if (!syberos) {
            this.os.h5 = true;
        }
    };

    detect.call(hybridJs, navigator.userAgent);
}