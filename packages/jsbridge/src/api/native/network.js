import hybridJs from '../../hybrid';

export default function networkMixin() {

    hybridJs.extendModule('network', [
        {
            namespace: 'request',
            os: ['syberos']
        }

    ]);
}
