import hybridJs from '../../hybrid';

export default function qrcodeMixin () {
    hybridJs.extendModule('qrcode', [{
      namespace: 'scan',
      os: ['syberos'],
    }]);
}