// InfoView.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleSniffer.h"
#include "InfoView.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_MESSAGE(WM_TCATCH, OnTCatch)
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

	m_list.InsertColumn( 0, "时间", LVCFMT_CENTER, 110); 
	m_list.InsertColumn( 1, "源MAC", LVCFMT_CENTER, 120 );
	m_list.InsertColumn( 2, "目的MAC", LVCFMT_CENTER, 120 );
	m_list.InsertColumn( 3, "长度", LVCFMT_CENTER,120 );
}
