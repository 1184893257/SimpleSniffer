// PackInfo.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleSniffer.h"
#include "PackInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPackInfo

IMPLEMENT_DYNCREATE(CPackInfo, CEditView)

CPackInfo::CPackInfo()
{
	// CPackInfo 是用来显示抓到的包的各层PDU详细信息的
	theApp.m_packInfo = this;
}

CPackInfo::~CPackInfo()
{
}


BEGIN_MESSAGE_MAP(CPackInfo, CEditView)
	//{{AFX_MSG_MAP(CPackInfo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPackInfo drawing

void CPackInfo::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPackInfo diagnostics

#ifdef _DEBUG
void CPackInfo::AssertValid() const
{
	CEditView::AssertValid();
}

void CPackInfo::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPackInfo message handlers


// 初始化中设置编辑区为只读
void CPackInfo::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	static BOOL inited = FALSE;
	if(inited) return;
	inited = TRUE;
	// 以下代码只在首次调用 OnInitialUpdate 时执行

	CEdit& control = this->GetEditCtrl();
	control.SetReadOnly();// 编辑区只读, 不允许手动更改
}

// 在编辑区中显示一段字符串
void CPackInfo::ShowPackInfo(const CString& info)
{
	this->SetWindowText(info);
}
