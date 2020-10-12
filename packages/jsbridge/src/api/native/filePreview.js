/**
 * 存储
 */
import hybridJs from '../../hybrid';

export default function filePreviewMixin() {
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('filePreview', [{
        namespace: 'previewText',
        os: ['syberos'],
        defaultParams: {
            path: ''
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'path'
            );
            hybridJs.callInner.apply(this, args);
        },
    }]);
}