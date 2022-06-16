import hybridJs from '../../hybrid';

export default function StorageSpaceMixin() {

    hybridJs.extendModule('StorageSpace', [
        {
            namespace: 'getSystemStorage',
            os: ['syberos'],
        },
        {
            namespace: 'getSystemRoot',
            os: ['syberos'],
        },
        {
            namespace: 'getSystemData',
            os: ['syberos'],
        },
		{
            namespace: 'getIntStorage',
            os: ['syberos'],
        },
		{
            namespace: 'getExtStorage',
            os: ['syberos'],
        },
		{
            namespace: 'getMemory',
            os: ['syberos'],
        },
    ]);
}
