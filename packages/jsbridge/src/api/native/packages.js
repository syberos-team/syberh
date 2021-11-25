import hybridJs from '../../hybrid';

export default function packagesMixin() {
    hybridJs.extendModule('packages', [{
        namespace: 'openUrl',
        os: ['syberos'],
    }, {
        namespace: 'openDocument',
        os: ['syberos'],
    }]);
}
