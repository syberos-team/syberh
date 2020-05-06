import hybridJs from '../../hybrid';

export default function navigatorMixin () {
  const innerUtil = hybridJs.innerUtil;

  /**
   * 按钮最多允许6个英文字符，或3个中文
   */
  const MAX_BTN_TEXT_COUNT = 6;

  hybridJs.extendModule('navigator', [{
    namespace: 'setTitle',
    os: ['syberos'],
    defaultParams: {
      title: '',
      // 子标题
      subTitle: '',
      // 是否可点击，可点击时会有点击效果并且点击后会触发回调，不可点击时永远不会触发回调
      // 可点击时，title会有下拉箭头
      // promise调用时和其他长期回调一样立马then
      direction: 'bottom',
      // 是否可点击，如果为1，代表可点击，会在标题右侧出现一个下拉图标，并且能被点击监听
      clickable: 0,
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'title');

      this.api.isLongCb = true;

      hybridJs.callInner.apply(this, args);
    },
  }, {
    namespace: 'setMultiTitle',
    os: ['syberos'],
    defaultParams: {
      titles: '',
    },
    runCode (...rest) {
      this.api.isLongCb = true;

      hybridJs.callInner.apply(this, rest);
    },
  }, {
    namespace: 'show',
    os: ['syberos'],
  }, {
    namespace: 'hide',
    os: ['syberos'],
  }, {
    namespace: 'showStatusBar',
    os: ['syberos'],
  }, {
    namespace: 'hideStatusBar',
    os: ['syberos'],
  }, {
    namespace: 'hideBackButton',
    os: ['syberos'],
  }, {
    namespace: 'hookSysBack',
    os: ['syberos'],
    runCode (...rest) {
      this.api.isLongCb = true;

      hybridJs.callInner.apply(this, rest);
    },
  }, {
    namespace: 'hookBackBtn',
    os: ['syberos'],
    runCode (...rest) {
      this.api.isLongCb = true;

      hybridJs.callInner.apply(this, rest);
    },
  }, {
    namespace: 'setRightBtn',
    os: ['syberos'],
    defaultParams: {
      text: '',
      imageUrl: '',
      isShow: 1,
      // 对应哪一个按钮，一般是0, 1可选择
      which: 0,
    },
    runCode (...rest) {
      const args = rest;
      const options = args[0];

      options.imageUrl = options.imageUrl && innerUtil.getFullPath(options.imageUrl);
      options.text = innerUtil.eclipseText(options.text, MAX_BTN_TEXT_COUNT);

      args[0] = options;
      this.api.isLongCb = true;

      hybridJs.callInner.apply(this, args);
    },
  }, {
    namespace: 'setRightMenu',
    os: ['syberos'],
    defaultParams: {
      text: '',
      imageUrl: '',
      // 过滤色默认为空
      iconFilterColor: '',
      // 点击后出现的菜单列表，这个API会覆盖rightBtn
      titleItems: [],
      iconItems: [],
    },
    /**
     * 这个API比较特殊，暂时由前端模拟
     */
    runCode (...rest) {
      const newArgs = [].slice.call(rest);
      const newOptions = innerUtil.extend({}, newArgs[0]);

      newOptions.success = () => {
        // 点击的时候，弹出菜单
        hybridJs.ui.popWindow.apply(this, rest);
      };

      newArgs[0] = newOptions;
      hybridJs.navigator.setRightBtn.apply(this, newArgs);
    },
  }, {
    namespace: 'setLeftBtn',
    os: ['syberos'],
    defaultParams: {
      text: '',
      imageUrl: '',
      isShow: 1,
      // 是否显示下拉箭头,如果带箭头，它会占两个位置，同时覆盖左侧按钮和左侧返回按钮
      isShowArrow: 0,
    },
    runCode (...rest) {
      const args = rest;
      const options = args[0];

      options.imageUrl = options.imageUrl && innerUtil.getFullPath(options.imageUrl);
      options.text = innerUtil.eclipseText(options.text, MAX_BTN_TEXT_COUNT);

      args[0] = options;
      this.api.isLongCb = true;

      hybridJs.callInner.apply(this, args);
    },
  }]);
}