export default function systemMixin(hybrid) {
    const hybridJs = hybrid;

    hybridJs.extendModule('system', [
        {
            namespace: 'aboutPhone',
            os: ['syber']
        },
        {
            namespace: 'getResolution',
            os: ['syber']
        },
        {
            namespace: 'getCoreVersion',
            os: ['syber']
        },
        {
            namespace: 'getSysVersionID',
            os: ['syber']
        },
    ]);
}
