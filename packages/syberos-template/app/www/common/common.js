(function () {
  var html = ' \
        <header id="header" class="mui-bar mui-bar-nav style="margin-top:90px">\
            <a class="mui-action-back mui-icon mui-icon-left-nav  mui-pull-left"></a>\
            <h1 id="title" class="mui-title">{{TITLE}}</h1>\
            <a id="info" class="mui-icon mui-icon-more icon-white mui-pull-right hidden"></a>\
        </header>\
        '

  var fileName = window.location.href.match(/([^/]+).html/)[1]

  if (!fileName || fileName === 'index') {
    fileName = 'Hybrid API'
  }

  html = html.replace('{{TITLE}}', fileName)

  const div = document.createElement('div')
  div.innerHTML = html
  document.body.insertBefore(div, document.body.children[0])
  document.querySelector('.mui-content').style.paddingTop = '45px'

  mui('.mui-table-view').on('tap', '.api-class', function () {
    console.log('---runapi', typeof window.runApi)
    window.runApi && runApi(this.id)
  })

  window.showTips = function (msg, isAlert) {
    if (isAlert) {
      quick.ui.alert(msg, '提示')
    } else {
      quick.ui.toast(msg)
    }
  }
}())
