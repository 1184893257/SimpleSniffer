// SimpleSnifferDoc.h : interface of the CSimpleSnifferDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLESNIFFERDOC_H__3B960F4E_E825_4732_9E15_FE607E156361__INCLUDED_)
#define AFX_SIMPLESNIFFERDOC_H__3B960F4E_E825_4732_9E15_FE607E156361__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSimpleSnifferDoc : public CDocument
{
protected: // create from serialization only
	CSimpleSnifferDoc();
	DECLARE_DYNCREATE(CSimpleSnifferDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleSnifferDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSimpleSnifferDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSimpleSnifferDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLESNIFFERDOC_H__3B960F4E_E825_4732_9E15_FE607E156361__INCLUDED_)
