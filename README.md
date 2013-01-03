<h1 align="center"><b>SimpleSniffer 抓包软件</b></h1>

源代码托管在github：[https://github.com/1184893257/SimpleSniffer](https://github.com/1184893257/SimpleSniffer)  
最新版本编译好后的压缩包：[百度网盘](http://pan.baidu.com/share/link?shareid=167145&uk=3607536922)

# 一、安装、运行

1. 安装 4.1.1-WinPcap.exe  
本程序是基于 WinPcap 库的抓包软件，
要安装 WinPcap 之后才能正常运行。
2. 打开 Output\SimpleSniffer.exe 启动抓包程序

# 二、操作

## 打开网卡抓包

1. 点击工具栏第一个按钮

	![工具栏](https://github.com/1184893257/SimpleSniffer/blob/master/img/toolbar0.jpg?raw=true)
2. 在弹出的对话框中选择要监听的网卡

	![选择网卡](https://github.com/1184893257/SimpleSniffer/blob/master/img/selectdev.jpg?raw=true)

	点击确定，之后开始抓包

	![抓包](https://github.com/1184893257/SimpleSniffer/blob/master/img/catching.jpg?raw=true)

3. 选中列表中的某行，可显示各层协议PDU的详情、以及整个PDU的16进制形式

	![详细](https://github.com/1184893257/SimpleSniffer/blob/master/img/details.jpg?raw=true)

## 将抓到的所有包保存到一个pcap文件中

1. 点击工具栏第4个按钮终止当前抓包

	![工具栏2](https://github.com/1184893257/SimpleSniffer/blob/master/img/toolbar2.jpg?raw=true)

	工具栏又恢复为这个样子：

	![工具栏](https://github.com/1184893257/SimpleSniffer/blob/master/img/toolbar0.jpg?raw=true)

2. 点击保存按钮，弹出保存对话框，输入文件名，保存

	![保存](https://github.com/1184893257/SimpleSniffer/blob/master/img/save.jpg?raw=true)

## 打开pcap文件，重现抓到的数据包

1. 点击打开按钮，选中一个pcap文件

	![打开](https://github.com/1184893257/SimpleSniffer/blob/master/img/open.jpg?raw=true)

2. 保存在pcap文件中的所有包将重现出来：

	![重现](https://github.com/1184893257/SimpleSniffer/blob/master/img/reshow.jpg?raw=true)

---

# 源码框架

![modules](https://github.com/1184893257/SimpleSniffer/blob/master/docs/general/modules.png?raw=true)

更多介绍：

* [概要设计](https://github.com/1184893257/SimpleSniffer/blob/master/docs/general/general.md)
* [详细设计](https://github.com/1184893257/SimpleSniffer/blob/master/docs/detail/details.md)
* [测试文档](https://github.com/1184893257/SimpleSniffer/blob/master/docs/test/test.md)

---

# 目录/文件结构

* README.md  
用户手册、项目介绍
* Lib  
WinPcap库文件目录
* Include  
WinPcap头文件目录
* SimpleSniffer  
<b>抓包程序的源代码</b>
* docs  
文档
* img  
README 文件中使用到的图片
* test  
测试项目目录——存放各种测试项目
(<b>每个测试项目在 test 文件夹中建立一个独立的子文件夹</b>)

---

# 其他资料

* Markdown
	* 教程：
<a target="_blank" href="http://www.ituring.com.cn/article/details/504">Markdown语法说明（详解版）</a>
	* 编辑+渲染工具：
<a target="_blank" href="http://markdownpad.com/">MarkdownPad</a>
* git
	* 教程：
<a target="_blank" href="http://wenku.baidu.com/view/dfeb0a24af45b307e871978c.html">EGIT使用手册</a>  
虽然是介绍 EGIT 的，但是后半部分使用 git 是通用的，
而且解释得很好。
