import * as os from 'os'
import * as path from 'path'
import * as fs from 'fs-extra'
import chalk from 'chalk'


const SYBERH_CONFIG_PATH = path.join(os.homedir(), '.config/syberh.json')

export interface LocalConfigData {
    userPassword?: string
}


export class LocalConfig {

    private configPath: string = SYBERH_CONFIG_PATH

    private configData: LocalConfigData|undefined

    constructor(){
        this.configData = {}
    }

    load(): boolean {
        if(!this.configPath || !fs.existsSync(this.configPath)){
            return false
        }
        let data: LocalConfigData | undefined
        try{
            data = fs.readJsonSync(this.configPath, {encoding: 'utf-8'})
        }catch(e) {
            console.log(chalk.yellow(`无法访问文件：${this.configPath}`))
            console.log(e)
            return false
        }

        if(!data){
            return false
        }
        this.configData = data
        this.decodeConfigData()
        return true;
    }

    save() {
        if(!this.configData || Object.keys(this.configData).length === 0){
            return
        }
        const dir = path.dirname(this.configPath)
        if(!fs.pathExistsSync(dir)){
            fs.mkdirsSync(dir)
        }
        
        this.encodeConfigData()
        try{
            fs.writeJSONSync(this.configPath, this.configData, {encoding: 'utf-8', spaces:'\t', EOL:'\n'})
        }catch(e){
            console.log(chalk.yellow(`无法保存文件：${this.configPath}`))
            console.log(e)
        }
    }

    getConfig(): LocalConfigData|undefined{
        return this.configData
    }

    getUserPassword(): string|undefined {
        return this.configData?.userPassword
    }

    setUserPassword(userPassword: string) {
        if(!userPassword){
            return
        }
        if(!this.configData){
            this.configData = {}
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

