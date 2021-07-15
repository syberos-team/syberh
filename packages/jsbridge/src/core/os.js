/**
 * 加入系统判断功能
 */
import hybridJs from '../hybrid';

export default function osMixin() {
    const detect = function detect(ua) {
        this.os = {};

        const symbol = 'SyberOS';
        const syberosIdx = ua.indexOf(symbol);
        if(syberosIdx < 0){
            this.os.h5 = true;
            return;
        }
        this.os.syberos = true;

        const lastStr = ua.substr(syberosIdx);
        const semicolonIdx = lastStr.indexOf(';');
        if(semicolonIdx < 0){
            // bad user agent
            this.os.version = '5.0.0';
            this.os.qtVersion = '5.12.2'
            return;
        }
        const versionStr = lastStr.substring(symbol.length, semicolonIdx).trim();

        if(versionStr.indexOf('5') === 0){
            // os 5
            this.os.version = versionStr;
            this.os.qtVersion = '5.12.2';

            const qtIdx = lastStr.indexOf('QtWebEngine');
            const chromeIdx = lastStr.indexOf('Chrome');
            if(qtIdx < 0 || chromeIdx < 0){
                // bad qt version
                return;
            }
            const qtVersion = lastStr.substring(qtIdx + 12, chromeIdx);
            if(!qtVersion){
                return;
            }
            this.os.qtVersion = qtVersion.trim();
        }else{
            // os 2, 4
            this.os.version = '4.1.1';
            this.os.qtVersion = '5.9.6';

            const versions = versionStr.split(' ');
            if(!versions || versions.length != 2){
                // bad version
                return;
            }
            this.os.version = versions[0].trim();
            this.os.qtVersion = versions[1].trim();
        }
    };

    detect.call(hybridJs, navigator.userAgent);
}