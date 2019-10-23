# syberh-filepicker
> 文件选择插件，支持筛选特定类型的文件，支持设置选择的最大数量

## 如何使用
``` javascript
import syberh_filepicker 1.0

SFilesPicker {
    // 页面标题
    titleText: '文件选择'
    // 左侧返回按钮是否展示
    leftItemEnabled: true
    // 文件类型
    categoryType: 'all' // all, image, video, audio, document, text
    // 选择文件的最大数量
    count: 10
}
```