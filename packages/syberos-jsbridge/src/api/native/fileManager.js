export default function fileManagerMixin(hybrid) {
    const hybridJs = hybrid;

    hybridJs.extendModule('fileManager', [
        {
            namespace: 'copy',
            os: ['syber'],
            defaultParams: {
                srcPath: '',
                destPath: '',
            },
        },
        {
            namespace: 'move',
            os: ['syber'],
            defaultParams: {
                srcPath: '',
                destPath: '',
            },
        },
        {
            namespace: 'fileList',
            os: ['syber'],
            defaultParams: {
                srcPath: '',
            },
        },
        {
            namespace: 'getInfo',
            os: ['syber'],
            defaultParams: {
                srcPath: '',
            },
        },
    ]);
}
