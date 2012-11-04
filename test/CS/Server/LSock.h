#if !defined(AFX_LSOCK_H__28175BBA_C821_49D1_B1C0_662475025996__INCLUDED_)
#define AFX_LSOCK_H__28175BBA_C821_49D1_B1C0_662475025996__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LSock.h : header file
//

typedef struct
{
	char name[32];
	char data[480];
}_DATA;

class CServerDlg;

/////////////////////////////////////////////////////////////////////////////
// CLSock command target

class CLSock : public CSocket
{
// Attributes
public:

// Operations
public:
	CLSock(CServerDlg *p);
	virtual ~CLSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSock)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CLSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CServerDlg *m_p;
};

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// CRWSock command target

class CRWSock : public CSocket
{
// Attributes
public:

// Operations
public:
	CRWSock(CServerDlg *p);
	virtual ~CRWSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRWSock)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRWSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CServerDlg *m_p;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSOCK_H__28175BBA_C821_49D1_B1C0_662475025996__INCLUDED_)
