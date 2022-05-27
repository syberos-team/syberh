import hybridJs from '../../hybrid';

export default function LocationMixin() {

    hybridJs.extendModule('Location', [
        {
            namespace: 'currentPosition',
            os: ['syberos'],
        },
    ]);
}
