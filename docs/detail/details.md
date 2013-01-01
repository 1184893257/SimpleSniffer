<h1 align="center"><b>详细设计
</b></h1>

# 控制部分

* CMainFrame 主框架类
	* BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)  
	此函数创建了包含3个视图的分隔窗体
	* void CMainFrame::OnSelectstart()  
	<b>点击了"开始"工具栏按钮</b>, 弹出 CDevSelector 选中设备进行抓包
	* void CMainFrame::OnEndcatch()  
	<b>点击了"终止"工具栏按钮</b>, pcap\_breakloop 正在监听的设备
	* void CMainFrame::OnTExit(int exitNum)  
	得到线程退出前发出的 WM_TEXIT 消息, 可以安全地释放各种资源了
	* void CMainFrame::OnUpdateXXX(CCmdUI* pCmdUI)  
	开始、终止、打开、保存、另存为 按钮/菜单 的使能转换
* CDevSelector 网卡设备选择
	* void CDevSelector::InitWinPcap()  
	CDevSelector 初始化的时候获取设备列表
	* BOOL CDevSelector::OnInitDialog()  
	对话框初始化时调用 InitWinPcap
	* void CDevSelector::OnOK()  
	点击了对话框的"确定"按钮, pcap_open 选中的设备
* CSimpleSnifferApp 主程序类
	* void CSimpleSnifferApp::startCatch()  
	<b>启动线程, 开始抓包</b>
* CSimpleSnifferDoc 文档类
	* void CSimpleSnifferDoc::Serialize(CArchive& ar)  
	<b>串行化中实现 保存/打开 逻辑</b>

# 抓包线程

* UINT ThreadProc(LPVOID param)  
<b>抓包线程体，用 pcap_loop 循环抓包</b>
* static void packet\_handler(u\_char *param, const struct pcap\_pkthdr *header, const u\_char *pkt\_data)  
pcap\_loop 捕获到一个包后将包数据复制一份 并 发出WM_TCATCH消息
* class ThreadParam  
封装传给线程的参数

# 分隔视图

* CInfoView 包信息列表
	* void CInfoView::OnTCatch(struct pcap\_pkthdr \*header, u\_char \*pkt\_data)  
	<b>处理抓包线程抓到包的事件, pkt\_data 是抓到的包</b>
	* void CInfoView::OnClick(NMHDR* pNMHDR, LRESULT* pResult)  
	<b>点击列表中某行后, 显示它的包类型、16进制形式的包数据</b>
	* void CInfoView::clearList()  
	清空列表, 开始新的抓包前调用这个这个函数
* CPackInfo 各层协议单元详细信息  
	* void CPackInfo::ShowPackInfo(const CString& info)  
	在编辑区中显示一段字符串
* Hex 提供16进制显示的接口
	* virtual void ShowHexText(char *data, int len)=0;  
	以十六进制形式显示 data 之后的 len 个字节
* CHexView Hex接口的实现
	* void CHexView::ShowHexText(char *data, int len)  
	显示十六进制信息

# 解析包

<ul>
<li>class Head_Super 解析包的类，<b>所有包都派生自这个类</b>
<pre><code>class Head_Super{
public:<b>
	// 指向更高层协议
	Head_Super* next;
	// 从 pkt_data 中抽取出这层协议PDU的信息
	virtual void analysis(u_char *pkt_data)=0;</b>
	// 将这层协议的详细信息以一个字符串表现出来
	virtual CString my_print()=0;
};</code></pre></li>
<li>class Info 保存了抓到的一个包的所有信息
<pre><code>class Info{
public:
	struct pcap_pkthdr *header;	//抓包所得数据包一些信息（时间、长度）
	u_char *pkt_data;			//抓包所得数据包内容头指针<b>
	Head_Super* m_Head;			//最底层协议的PDU</b>
};</code></pre></li>
<li>class Head_XXX<br>
Head_Super 具体于某种协议的实现</li>
</ul>
