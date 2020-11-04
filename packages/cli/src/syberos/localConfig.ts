import * as os from 'os'
import * as path from 'path'
import * as fs from 'fs-extra'


const SYBERH_CONFIG_PATH = path.join(os.homedir(), '.config/syberh.json')

export interface LocalConfigData {
    userPassword?: string
}


export class LocalConfig {

    private configPath: string = SYBERH_CONFIG_PATH

    private configData: LocalConfigData

    constructor(){
        this.configData = {}
    }

    load(): boolean {
        if(!this.configPath || !fs.existsSync(this.configPath)){
            return false
        }
        const data = fs.readJsonSync(this.configPath, {encoding: 'utf-8'})
        if(!data){
            return false
        }
        this.configData = data
        this.decodeConfigData()
        return true;
    }

    save() {
        const dir = path.dirname(this.configPath)
        if(!fs.pathExistsSync(dir)){
            fs.mkdirsSync(dir)
        }
        if(Object.keys(this.configData).length === 0){
            return
        }
        this.encodeConfigData()
        fs.writeJSONSync(this.configPath, this.configData, {encoding: 'utf-8'})
    }

    getConfig(): LocalConfigData{
        return this.configData
    }

    getUserPassword(): string|undefined {
        return this.configData?.userPassword
    }

    setUserPassword(userPassword: string) {
        if(!userPassword){
            return
        }
        this.configData.userPassword = userPassword
    }

    setSavePath(configPath: string){
        if(!configPath){
            return
        }
        this.configPath = configPath
    }

    private encodeConfigData() {
        if(!this.configData){
            return
        }
        if(this.configData.userPassword){
            // TODO 加密密码
        }
    }

    private decodeConfigData() {
        if(!this.configData){
            return
        }
        if(this.configData.userPassword){
            // TODO 解密密码
        }
    }

}

