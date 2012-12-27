// InfoView.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleSniffer.h"
#include "InfoView.h"
#include "Thread.h"
#include "Info.h"
#include "Head.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int count;
extern int packet_kind;
extern unsigned char m_SIP[4];
extern unsigned char m_DIP[4];
extern unsigned char m_SIPv6[16];
extern unsigned char m_DIPv6[16];
extern int ipv6;	
extern int remain_len;

/////////////////////////////////////////////////////////////////////////////
// CInfoView

IMPLEMENT_DYNCREATE(CInfoView, CListView)

CInfoView::CInfoView()
{
}

CInfoView::~CInfoView()
{
}


BEGIN_MESSAGE_MAP(CInfoView, CListView)
	//{{AFX_MSG_MAP(CInfoView)
	ON_MESSAGE(WM_TCATCH, OnTCatch)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoView drawing

void CInfoView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CInfoView diagnostics

#ifdef _DEBUG
void CInfoView::AssertValid() const
{
	CListView::AssertValid();
}

void CInfoView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfoView message handlers

void CInfoView::OnTCatch(struct pcap_pkthdr *header, u_char *pkt_data)
{
	struct tm *ltime;
	char timestr[16];						//用于存储时间
	CString line_num,m_len,m_smac,m_dmac;	//用于输出格式转化
	CString m_kind;							//用于记录类型
	CString m_cntl;							//用于测试是不是802.3帧
	CString m_packetkind;
	CString m_s_ip;
	CString m_d_ip;
	Info temp_info;							//用于添加所捕获的数据包
	u_char S_mac[6];						//存源MAC
	u_char D_mac[6];						//存目的MAC
	u_char Kind[2];							//存以太帧类型
	u_char Cntl[1];							//如果是802.3帧，就应该是03
	remain_len=header->len;					//初始化
	//存储数据包
	temp_info.header=header;
	temp_info.pkt_data=pkt_data;
	//temp_info.information=NULL;
	//temp_info.len=0;
	//m_info.push_back(temp_info);

	//处理header获得时间，长度信息
	ltime = localtime(&header->ts.tv_sec);
	strftime(timestr, sizeof(timestr), "%H:%M:%S", ltime);
	line_num.Format("%d", count++);                           //count是一个全局变量用于记录行号
	m_len.Format("%d",header->len);

	//处理pkt_data得到详细信息
	memcpy(D_mac,pkt_data,6);
	memcpy(S_mac,pkt_data+6,6);
	memcpy(Kind,pkt_data+12,2);
	memcpy(Cntl,pkt_data+16,1);
	m_dmac.Format("%02X-%02X-%02X-%02X-%02X-%02X",D_mac[0],D_mac[1],D_mac[2],D_mac[3],D_mac[4],D_mac[5]);
	m_smac.Format("%02X-%02X-%02X-%02X-%02X-%02X",S_mac[0],S_mac[1],S_mac[2],S_mac[3],S_mac[4],S_mac[5]);
	m_kind.Format("%02X%02X",Kind[0],Kind[1]);
	m_cntl.Format("%02X",Cntl[0]);

	//第二步详细分析
	
	if(m_kind.Compare("0800")==0 || m_kind.Compare("0806")==0 || m_kind.Compare("86DD")==0)
	{
		temp_info.m_Head=new Head_Ethernet();
		temp_info.m_Head->analysis(pkt_data);
	}
	else
	{
		temp_info.m_Head=new Head_802_3();
		temp_info.m_Head->analysis(pkt_data);
	}
	
	m_info.push_back(temp_info);
	if(ipv6==0)
	{
		m_s_ip.Format("%u.%u.%u.%u",m_SIP[0],m_SIP[1],m_SIP[2],m_SIP[3]);
		m_d_ip.Format("%u.%u.%u.%u",m_DIP[0],m_DIP[1],m_DIP[2],m_DIP[3]);
	}
	else
	{
		m_s_ip.Format("%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X",m_SIPv6[0],m_SIPv6[1],m_SIPv6[2],m_SIPv6[3],m_SIPv6[4],m_SIPv6[5],m_SIPv6[6],m_SIPv6[7],m_SIPv6[8],m_SIPv6[9],m_SIPv6[10],m_SIPv6[11],m_SIPv6[12],m_SIPv6[13],m_SIPv6[14],m_SIPv6[15]);
		m_d_ip.Format("%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X",m_DIPv6[0],m_DIPv6[1],m_DIPv6[2],m_DIPv6[3],m_DIPv6[4],m_DIPv6[5],m_DIPv6[6],m_DIPv6[7],m_DIPv6[8],m_DIPv6[9],m_DIPv6[10],m_DIPv6[11],m_DIPv6[12],m_DIPv6[13],m_DIPv6[14],m_DIPv6[15]);
	}
	switch(packet_kind){
	case 0:m_packetkind="Ethernet";break;
	case 1:m_packetkind="802.3";break;
	case 2:m_packetkind="ARP";break;
	case 3:m_packetkind="IP";break;
	case 4:m_packetkind="ICMPv6";break;
	case 5:m_packetkind="UDP";break;
	case 6:m_packetkind="IGMPv3";break;
	case 7:m_packetkind="TCP";break;
	case 8:m_packetkind="IPv6";break;
	case 9:m_packetkind="OSPF";break;
	case 10:m_packetkind="DNS";break;
	case 11:m_packetkind="HTTP";break;
	case 12:m_packetkind="FTP";break;
	}
	//在列表中显示
	CListCtrl& ctr = this->GetListCtrl();
	
	int row = ctr.InsertItem(ctr.GetItemCount(), line_num);   //获得当前所要输出的行号
	ctr.SetItemText(row, 1, timestr);
	ctr.SetItemText(row, 2, m_dmac);
	ctr.SetItemText(row, 3, m_smac);
	ctr.SetItemText(row, 4, m_len);
	ctr.SetItemText(row, 5, m_kind);
	ctr.SetItemText(row, 6, m_cntl);
	ctr.SetItemText(row, 7, m_s_ip);
	ctr.SetItemText(row, 8, m_d_ip);
	ctr.SetItemText(row, 9, m_packetkind);
	// 抓到包后设置文档已修改, 退出的时候就会提醒用户保存 dump 文件
	this->GetDocument()->SetModifiedFlag();
}

void CInfoView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	static BOOL inited = FALSE;
	if(inited) return;
	inited = TRUE;
	// 以下代码只在首次调用 OnInitialUpdate 时执行
	
	theApp.m_display = this->GetSafeHwnd();
	CListCtrl& m_list = GetListCtrl();
	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle); 
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_list.SetExtendedStyle(dwStyle);
	m_list.SetBkColor(RGB(200, 200, 200));
	m_list.SetTextBkColor(RGB(200, 200, 200));
	m_list.SetTextColor(RGB(10, 10, 80));
	
	m_list.InsertColumn( 0, "序号", LVCFMT_CENTER, 50);
	m_list.InsertColumn( 1, "时间", LVCFMT_CENTER, 80); 
	m_list.InsertColumn( 2, "源MAC", LVCFMT_CENTER, 130 );
	m_list.InsertColumn( 3, "目的MAC", LVCFMT_CENTER, 130 );
	m_list.InsertColumn( 4, "长度", LVCFMT_CENTER,100 );
	m_list.InsertColumn( 5, "类型",LVCFMT_CENTER,80);
	m_list.InsertColumn( 6, "802.3",LVCFMT_CENTER,50);

	//第二步详细分析显示
	m_list.InsertColumn( 7,"源IP",LVCFMT_CENTER, 180 );
	m_list.InsertColumn( 8,"目的IP",LVCFMT_CENTER, 180 );
	m_list.InsertColumn( 9,"包类型",LVCFMT_CENTER, 130 );
}

void CInfoView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	NMLISTVIEW* pList = (NMLISTVIEW*)pNMHDR;
	CString m_message;						//初始化就是空的
	Head_Super* head_temp;
    int iItem = pList->iItem;
    if(iItem != -1)
    {
        theApp.m_editor->ShowHexText((char*)m_info[iItem].pkt_data, m_info[iItem].header->len);
		//theApp.m_packInfo->ShowPackInfo("第1行\r\n第2行");
		head_temp=m_info[iItem].m_Head;
		while(head_temp!=NULL)
		{
			m_message=m_message+head_temp->my_print()+"\r\n";
			head_temp=head_temp->next;
		}
		theApp.m_packInfo->ShowPackInfo(m_message);
    }
    *pResult = 0;
}
