#if !defined(AFX_WCSOCK_H__1770D5A4_0DAB_4E66_81BD_A147C851EFF6__INCLUDED_)
#define AFX_WCSOCK_H__1770D5A4_0DAB_4E66_81BD_A147C851EFF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WCSock.h : header file
//

typedef struct
{
	char name[32];
	char data[480];
}_DATA;

#define RE_RECEIVED WM_USER + 1

/////////////////////////////////////////////////////////////////////////////
// CWCSock command target

class CWCSock : public CSocket
{
// Attributes
public:

// Operations
public:
	CWCSock();
	virtual ~CWCSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWCSock)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CWCSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	_DATA m_Dat;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WCSOCK_H__1770D5A4_0DAB_4E66_81BD_A147C851EFF6__INCLUDED_)
