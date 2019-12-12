export default function qrcodeMixin (hybrid) {
    const hybridJs = hybrid;
  
    hybridJs.extendModule('qrcode', [{
      namespace: 'scan',
      os: ['syberos'],
    }]);
}