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

void CInfoView::OnTCatch(const struct pcap_pkthdr *header, const u_char *pkt_data)
{

}
