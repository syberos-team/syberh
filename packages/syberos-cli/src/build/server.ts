
import Server, { Watcher } from '@syberos/dev-server'

export default class DevServer {
  private port: number = 4399;
  private watchPath: string;
  constructor(watchPath) {
    this.watchPath = watchPath;
    this.start();
  }
  public start() {
    const server = new Server({ port: this.port })
    // tslint:disable-next-line: no-unused-expression
    new Watcher(server, this.watchPath)
  }
}