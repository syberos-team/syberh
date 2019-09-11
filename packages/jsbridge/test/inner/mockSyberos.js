
const navigator = window.navigator;

console.log(navigator.userAgent);
if (!navigator.qt) {
    console.log('no navigator', navigator);
    navigator.qt = {};

    navigator.qt.postMessage = function (message) {
        console.log('on message', message);

        console.log(window.JSBridge);

        window.JSBridge._handleMessageFromNative({ responseId: '111', responseData: { test: 'test' } });
    };

    navigator.qt.onmessage = function () {

    };
}
