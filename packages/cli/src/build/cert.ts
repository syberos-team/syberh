import * as fs from 'fs-extra'
import * as path from 'path'
import { isTargetOS_5 } from '../syberos/helper'


export class CertError extends Error {
    private msg :string
    constructor(msg) {
      super(msg)
      this.name = 'CertError'
      this.msg = msg;
    }

    getMessage() : string{
        return this.msg;
    }
}

export interface CertConfig {
    // syberh应用的根目录
    appPath: string
    // 
    targetName : string
}

type CertContainer = {
    name : string
    content: string
}

export class CertGenerator {
    private conf : CertConfig
    private metaInfoPath : string

    constructor(conf:CertConfig){
        this.conf = conf;
        this.metaInfoPath = path.join(this.conf.appPath, 'platforms/syberos/META-INF');
    }

    generate() : string{
        this.certChecker();

        let certContainer : CertContainer;
        if(isTargetOS_5(this.conf.targetName)){
            certContainer = this.loadCert('OS_5');
        }else{
            certContainer = this.loadCert('OS_old');
        }
        return this.createCert(certContainer);
    }

    private createCert(container : CertContainer) : string{
        if(!container || !container.name || !container.content){
            throw new CertError('证书内容为空，生成失败');
        }
        const certFilePath = path.join(this.metaInfoPath, container.name);
        fs.writeFileSync(certFilePath, container.content);
        return certFilePath;
    }

    private loadCert(filename : string) : CertContainer {
        const certObj = require('./cert/' + filename + '.js')
        return {
            name: certObj.CERT_NAME,
            content: certObj.CERT_CONTENT
        }
    }

    // META-INF 中存在证书时不生成新证书
    private certChecker() {
        if(!fs.pathExistsSync(this.metaInfoPath)){
            fs.mkdirsSync(this.metaInfoPath);
        }
        const files = fs.readdirSync(this.metaInfoPath);
        for(const f of files){
            if(path.extname(f) === '.pem'){
                throw new CertError('已存在证书，不执行证书生成操作：' + f);
            }
        }
    }
}