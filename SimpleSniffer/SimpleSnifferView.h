// SimpleSnifferView.h : interface of the CSimpleSnifferView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLESNIFFERVIEW_H__06D2FD5F_CDD9_4F6D_B925_8667E73CE4B8__INCLUDED_)
#define AFX_SIMPLESNIFFERVIEW_H__06D2FD5F_CDD9_4F6D_B925_8667E73CE4B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <pcap.h>
#include <vector>
using namespace std;

class CSimpleSnifferDoc;

class CSimpleSnifferView : public CFormView
{
protected:
	vector<pcap_if_t *> m_devsArray;// 设备列表转换过来的数组

protected:
	void OnTExit(int exitNum);// 处理抓包线程退出的事件
	void InitWinPcap();	// 初始化 WinPcap

protected: // create from serialization only
	CSimpleSnifferView();
	DECLARE_DYNCREATE(CSimpleSnifferView)

public:
	//{{AFX_DATA(CSimpleSnifferView)
	enum { IDD = IDD_SIMPLESNIFFER_FORM };
	CComboBox	m_devsName;
	//}}AFX_DATA

// Attributes
public:
	CSimpleSnifferDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleSnifferView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSimpleSnifferView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSimpleSnifferView)
	afx_msg void OnStart();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SimpleSnifferView.cpp
inline CSimpleSnifferDoc* CSimpleSnifferView::GetDocument()
   { return (CSimpleSnifferDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLESNIFFERVIEW_H__06D2FD5F_CDD9_4F6D_B925_8667E73CE4B8__INCLUDED_)
