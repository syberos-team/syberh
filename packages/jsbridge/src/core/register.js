import hybridJs from '../hybrid';

export default function registerMixin() {
  hybridJs.register = function (plugin) {
    const properties = Object.getOwnPropertyNames(plugin.prototype)

    const curPlugin = new plugin()

    let arr = []

    for (let property of properties) {
      if (property.startsWith('method_')) {
        arr.push({
          namespace: property.substr(7),
          os: curPlugin['os'](),
          defaultParams: curPlugin[property]()
        })
      }
    }
    hybridJs.extendModule(curPlugin['module'](), arr)
  }
}
