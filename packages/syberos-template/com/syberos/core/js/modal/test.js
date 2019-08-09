/* eslint-disable no-undef */

/***
 * modal.test(Object)
 */
function Test () {
  var defaultOpts = {
    id: 'test',
    name: 'test',
    module: 'modal',
    methods: ['test'],
    source: '../qml/test.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this

  this.on('test', function (object) {

    console.log('\n')
    console.log('test ready', object)
    console.log('\n')
    var component = object || that.object
//    component.titleText = that.param.title
//    component.messageText = that.param.message
//    component.show()

//    component.accepted.connect(function () {
//      console.log('-----test accepted')
//    })
  })

}

Test.prototype = SyberPlugin.prototype
