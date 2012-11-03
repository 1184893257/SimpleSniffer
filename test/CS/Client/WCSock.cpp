// WCSock.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "WCSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWCSock

CWCSock::CWCSock()
{
}

CWCSock::~CWCSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CWCSock, CSocket)
	//{{AFX_MSG_MAP(CWCSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CWCSock member functions

void CWCSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(this->Receive(&this->m_Dat, sizeof(_DATA))==sizeof(_DATA))
		::PostMessage(::AfxGetApp()->m_pMainWnd->m_hWnd, RE_RECEIVED, (WPARAM)(&m_Dat), 0);
	CSocket::OnReceive(nErrorCode);
}
