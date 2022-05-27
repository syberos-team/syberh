import hybridJs from '../../hybrid';

export default function VolumeMixin() {

    hybridJs.extendModule('Volume', [
        {
            namespace: 'setVolume',
            os: ['syberos'],
            defaultParams: {
                volume: '',
                role: '',
            },
        },
        {
            namespace: 'getVolume',
            os: ['syberos'],
            defaultParams: {
                role: '',
            },
        },
    ]);
}
