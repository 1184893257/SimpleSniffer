// LSock.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "LSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLSock

CLSock::CLSock(CServerDlg *p)
{
	this->m_p=p;
}

CLSock::~CLSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CLSock, CSocket)
	//{{AFX_MSG_MAP(CLSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CLSock member functions
/////////////////////////////////////////////////////////////////////////////
// CRWSock

CRWSock::CRWSock(CServerDlg *p)
{
	this->m_p=p;
}

CRWSock::~CRWSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRWSock, CSocket)
	//{{AFX_MSG_MAP(CRWSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CRWSock member functions

#include "ServerDlg.h"

void CRWSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	this->m_p->ReadMessage(this);
	CSocket::OnReceive(nErrorCode);
}

void CLSock::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	this->m_p->AcceptClient();
	CSocket::OnAccept(nErrorCode);
}
