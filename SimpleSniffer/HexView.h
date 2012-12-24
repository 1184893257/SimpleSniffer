#if !defined(AFX_HEXVIEW_H__70817DC6_09E6_4920_867B_FC44E1B42890__INCLUDED_)
#define AFX_HEXVIEW_H__70817DC6_09E6_4920_867B_FC44E1B42890__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HexView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHexView view

class CHexView : public CEditView, public Hex
{
protected:
	CFont m_Font;		// 用于存储字体
protected:
	CHexView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHexView)

// Attributes
public:

// Operations
public:
	// 实现十六进制的显示, 是 Hex 的纯虚函数
	void ShowHexText(char *data, int len);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHexView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXVIEW_H__70817DC6_09E6_4920_867B_FC44E1B42890__INCLUDED_)
