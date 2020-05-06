import hybridJs from '../../hybrid';

export default function imageMixin() {
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('image', [
        {
            namespace: 'chooseImage',
            os: ['syberos'],
            defaultParams: {
                count: 9,
                sourceType: ['camera', 'album'],
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'count',
                    'sourceType',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
        {
            namespace: 'previewImage',
            os: ['syberos'],
            defaultParams: {
                urls: [],
                current: '',
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'urls',
                    'current',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
        {
            namespace: 'saveImageToPhotosAlbum',
            os: ['syberos'],
            defaultParams: {
                filePath: '',
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'filePath',
                );
                hybridJs.callInner.apply(this, args);
            },
        }, {
            namespace: 'getImageInfo',
            os: ['syberos'],
            runCode(...rest) {
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'path',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
    ]);
}