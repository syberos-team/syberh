// 参数
var opts = {
  id: 'rootItem',
  name: 'root',
  source: '../root.qml'
}

var RootItem = new SyberPlugin(opts)
RootItem.on('init', function () {
  console.log('\n ----rootItem-init')
  console.log('\n ----rootItem-init', JSON.stringify(RootItem))
})
