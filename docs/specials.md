---
title: 常见问题
---

- `热更新检测不到文件变化` 的问题处理

```bash
#设置 max_user_watches值
echo fs.inotify.max_user_watches=524288 | sudo tee -a /etc/sysctl.conf && sudo sysctl -p
```
