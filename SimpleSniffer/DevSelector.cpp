// DevSelector.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleSniffer.h"
#include "DevSelector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDevSelector dialog


CDevSelector::CDevSelector(CWnd* pParent /*=NULL*/)
	: CDialog(CDevSelector::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDevSelector)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDevSelector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevSelector)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDevSelector, CDialog)
	//{{AFX_MSG_MAP(CDevSelector)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDevSelector message handlers
