#if !defined(AFX_PACKINFO_H__69A9B60D_5CDA_486B_8487_5AF70BDE35E6__INCLUDED_)
#define AFX_PACKINFO_H__69A9B60D_5CDA_486B_8487_5AF70BDE35E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PackInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPackInfo view

class CPackInfo : public CEditView
{
protected:
	CPackInfo();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPackInfo)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPackInfo)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPackInfo();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPackInfo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PACKINFO_H__69A9B60D_5CDA_486B_8487_5AF70BDE35E6__INCLUDED_)
