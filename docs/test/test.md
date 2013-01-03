<h1 align="center"><b>测试文档
</b></h1>

<table border="1">
 <tr><td>测试目标</td>
  <td><b>十六进制的显示</b></td>
 </tr>
 <tr><td>测试方法</td>
  <td>添加按钮，在按钮的响应函数中调用十六进制显示函数，
  显示 0、1、2、3、……个字节长度的十六进制信息</td>
 </tr>
 <tr><td>完成标准</td>
  <td>格式正确、没有错误发生</td>
 </tr>
 <tr><td>测试结果</td>
  <td>符合要求</td>
 </tr>
</table>

## 相关截图

![hex](hex.jpg?raw=true)

---

<table border="1">
 <tr><td>测试目标</td>
  <td><b>抓包线程的启动和终止</b></td>
 </tr>
 <tr><td>测试方法</td>
  <td>1. 启动抓包线程后无网络活动，终止<br>
  2. 启动抓包线程后有网络活动，终止</td>
 </tr>
 <tr><td>完成标准</td>
  <td>两种情况线程都正常退出，并重置各按钮的状态</td>
 </tr>
 <tr><td>测试结果</td>
  <td>符合要求</td>
 </tr>
</table>

## 相关截图

### 无网络活动的 启动 和 终止

![nonetwork1](nonetwork1.jpg?raw=true)

![nonetwork2](nonetwork2.jpg?raw=true)

### 有网络活动的 启动 和 终止

![network1](network1.jpg?raw=true)

![network2](network2.jpg?raw=true)
