// base class that users should extend if they are making their own
// server implementation
export default class BaseServer {
  public server: any;
  constructor(server: any) {
    this.server = server;
  }
}