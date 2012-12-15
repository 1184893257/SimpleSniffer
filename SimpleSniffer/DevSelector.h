#if !defined(AFX_DEVSELECTOR_H__7E47099B_BD48_4971_AA41_CDB5DB7CB054__INCLUDED_)
#define AFX_DEVSELECTOR_H__7E47099B_BD48_4971_AA41_CDB5DB7CB054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DevSelector.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDevSelector dialog

class CDevSelector : public CDialog
{
// Construction
public:
	CDevSelector(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDevSelector)
	enum { IDD = IDD_SELECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevSelector)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDevSelector)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVSELECTOR_H__7E47099B_BD48_4971_AA41_CDB5DB7CB054__INCLUDED_)
