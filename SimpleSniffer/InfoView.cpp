// InfoView.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleSniffer.h"
#include "InfoView.h"
#include "Thread.h"
#include "Info.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int count;

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
	Info temp_info;							//用于添加所捕获的数据包
	u_char S_mac[6];						//存源MAC
	u_char D_mac[6];						//存目的MAC
	//存储数据包
	temp_info.header=header;
	temp_info.pkt_data=pkt_data;
	temp_info.information=NULL;
	temp_info.len=0;
	m_info.push_back(temp_info);

	//处理header获得时间，长度信息
	ltime = localtime(&header->ts.tv_sec);
	strftime(timestr, sizeof(timestr), "%H:%M:%S", ltime);
	line_num.Format("%d", count++);                           //count是一个全局变量用于记录行号
	m_len.Format("%d",header->len);

	//处理pkt_data得到详细信息
	memcpy(D_mac,pkt_data,6);
	memcpy(S_mac,pkt_data+6,6);
	m_dmac.Format("%02X-%02X-%02X-%02X-%02X-%02X",D_mac[0],D_mac[1],D_mac[2],D_mac[3],D_mac[4],D_mac[5],D_mac[6]);
	m_smac.Format("%02X-%02X-%02X-%02X-%02X-%02X",S_mac[0],S_mac[1],S_mac[2],S_mac[3],S_mac[4],S_mac[5],S_mac[6]);

	//在列表中显示
	CListCtrl& ctr = this->GetListCtrl();
	
	int row = ctr.InsertItem(ctr.GetItemCount(), line_num);   //获得当前所要输出的行号
	ctr.SetItemText(row, 1, timestr);
	ctr.SetItemText(row, 2, m_dmac);
	ctr.SetItemText(row, 3, m_smac);
	ctr.SetItemText(row, 4, m_len);
}

void CInfoView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
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
	m_list.InsertColumn( 2, "源MAC", LVCFMT_CENTER, 110 );
	m_list.InsertColumn( 3, "目的MAC", LVCFMT_CENTER, 110 );
	m_list.InsertColumn( 4, "长度", LVCFMT_CENTER,100 );
}

void CInfoView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	NMLISTVIEW* pList = (NMLISTVIEW*)pNMHDR;
    int iItem = pList->iItem;
    if(iItem != -1)
    {
        theApp.m_editor->ShowHexText((char*)m_info[iItem].pkt_data, m_info[iItem].header->len);
    }
    *pResult = 0;
}
