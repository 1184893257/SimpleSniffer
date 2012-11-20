// SimpleSnifferView.cpp : implementation of the CSimpleSnifferView class
//

#include "stdafx.h"
#include "SimpleSniffer.h"

#include "SimpleSnifferDoc.h"
#include "SimpleSnifferView.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferView

IMPLEMENT_DYNCREATE(CSimpleSnifferView, CFormView)

BEGIN_MESSAGE_MAP(CSimpleSnifferView, CFormView)
	//{{AFX_MSG_MAP(CSimpleSnifferView)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_MESSAGE(WM_TEXIT, OnTExit)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferView construction/destruction

CSimpleSnifferView::CSimpleSnifferView()
	: CFormView(CSimpleSnifferView::IDD)
{
	//{{AFX_DATA_INIT(CSimpleSnifferView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CSimpleSnifferView::~CSimpleSnifferView()
{
}

void CSimpleSnifferView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleSnifferView)
	DDX_Control(pDX, IDC_DEVS, m_devsName);
	//}}AFX_DATA_MAP
}

BOOL CSimpleSnifferView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSimpleSnifferView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	this->InitWinPcap();// 执行 WinPcap 初始化
	this->GetDlgItem(IDC_START)->EnableWindow(true);
	this->GetDlgItem(IDC_STOP)->EnableWindow(false);
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferView printing

BOOL CSimpleSnifferView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSimpleSnifferView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSimpleSnifferView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSimpleSnifferView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferView diagnostics

#ifdef _DEBUG
void CSimpleSnifferView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSimpleSnifferView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSimpleSnifferDoc* CSimpleSnifferView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpleSnifferDoc)));
	return (CSimpleSnifferDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferView message handlers

void CSimpleSnifferView::OnStart() 
{
	// TODO: Add your control notification handler code here
	char errbuf[PCAP_ERRBUF_SIZE];

	pcap_if_t *d = this->m_devsArray[this->m_devsName.GetCurSel()];

	if ((this->m_curDev = pcap_open(d->name, /* name of the device */
		65536,/* portion of the packet to capture , 65535 guarantees that the whole packet will be captured on all the link layers */
		PCAP_OPENFLAG_PROMISCUOUS,/* promiscuous mode */
		1000,/* read timeout */
		NULL,/* authentication on the remote machine */
		errbuf/* error buffer */)) == NULL)
	{
		::AfxMessageBox("打开适配器失败!");
		return;
	}
	::AfxBeginThread(ThreadProc, this->m_curDev);

	this->GetDlgItem(IDC_START)->EnableWindow(false);
	this->GetDlgItem(IDC_STOP)->EnableWindow(true);
}

void CSimpleSnifferView::OnStop() 
{
	// TODO: Add your control notification handler code here
	pcap_breakloop(this->m_curDev);
}

void CSimpleSnifferView::OnTExit(int exitNum)
{
	this->GetDlgItem(IDC_START)->EnableWindow(true);
	this->GetDlgItem(IDC_STOP)->EnableWindow(false);
}

void CSimpleSnifferView::InitWinPcap()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	char errbuf[PCAP_ERRBUF_SIZE];

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1){
		::AfxMessageBox("获取设备列表失败");
		return;
	}

	for (d = alldevs; d; d = d->next){
		this->m_devsName.AddString(d->description);
		this->m_devsArray.push_back(d);
	}

	this->UpdateData(false);
}
