/* eslint-disable no-undef */

/***
 * app.setPageOrientation(Object)
 */
function App () {
  var defaultOpts = {
    id: 'app',
    module: 'app',
    methods: ['setAppOrientation']
  };
  SyberPlugin.call(this, defaultOpts);

  var that = this;
  this.on('setAppOrientation', function () {
    var orientation = that.param.orientation;
    console.log('global setAppOrientation', orientation);

    if (!orientation && orientation != 0) {
      WEBVIEWCORE.trigger('failed', that.handlerId, 9001, 'orientation不能为空');
      return;
    }

    if (orientation != 0 && orientation != 1 && orientation != 2 && orientation != 8) {
      WEBVIEWCORE.trigger('failed', that.handlerId, 9001, 'orientation参数有误');
      return;
    }

    for (var i = 0; i < swebviews.length; i++) {
      // swebviews[i].object 是SWebview
      swebviews[i].object.setPageOrientation(orientation);
      WEBVIEWCORE.trigger('success', that.handlerId);
    }
    globalPageOrientation = orientation;
  });
}

App.prototype = SyberPlugin.prototype;
