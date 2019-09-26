/* eslint-disable no-undef */

/***
 * modal.toast(Object)
 */
function GToast () {
  var defaultOpts = {
    id: 'gtoast',
    name: 'gtoast',
    module: 'modal',
    methods: ['gtoast']
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this
  this.on('gtoast', function () {
    if (!that.param.title) {
      that.failed(that.handlerId, 1003, "提示的内容不能为空");
      return;
    }
    gToast.requestToast(that.param.title);
    that.success(that.handlerId);
  });
}

GToast.prototype = SyberPlugin.prototype
