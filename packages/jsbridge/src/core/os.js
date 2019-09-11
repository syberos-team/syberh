/**
 * 加入系统判断功能
 */
export default function osMixin(hybrid) {
    const hybridJs = hybrid;
    const detect = function detect(ua) {
        this.os = {};
        // syberhybrid的容器
        const syber = ua.match(/SyberOS/i);
        console.log('os', syber);
        if (syber) {
            this.os.syber = true;
        }

        // 如果不是SyberOS，则默认为h5
        if (!syber) {
            this.os.h5 = true;
        }
    };

    detect.call(hybridJs, navigator.userAgent);
}