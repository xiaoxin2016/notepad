# 简单记事本程序 Notepad

### 说明
- 这是 ~~帝国能源大学~~ 中国石油大学（华东）软件工程一年级小学期任务。
- 基于Qt Creator 4.3.1（Qt 5.9.1）和C++在macOS上创建的第一个界面程序。
- 代码参考Qt快速入门系列教程并进行修正。
- 其他文件问题邮件/wiki联系。
- 删掉了.user文件，您可根据自己的操作系统和环境设置以方便运行。(2017.7.13 added)

### 程序截图预览
程序运行界面：
![程序运行界面](https://raw.githubusercontent.com/andyliu24/notepad/master/Preview/1.png "程序运行界面")

查找功能演示：
![查找功能演示](https://raw.githubusercontent.com/andyliu24/notepad/master/Preview/2.png "查找功能演示")

### 尚存bug解释
- 在判断文件更改的`maybeSave`函数中，调用系统函数`isModified()`判断文本框是否被修改。但保存文档后立即点击新建/打开仍旧提示未保存，经单步调试发现`isModified()`返回值为true，没有想到好的解决方案，于是此bug没有修正。
- 其他未尽bug期待您的发觉。

### END
