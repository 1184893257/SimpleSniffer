#if !defined(AFX_INFOVIEW_H__9A1BF4A1_6A86_49F6_AD15_79A3B501B98A__INCLUDED_)
#define AFX_INFOVIEW_H__9A1BF4A1_6A86_49F6_AD15_79A3B501B98A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoView view
#include <pcap.h>
#include <vector>
#include "Info.h"
using namespace std;

class CInfoView : public CListView
{
protected:
	void OnTCatch(struct pcap_pkthdr *header, u_char *pkt_data);// 处理抓到包的事件
	vector<Info> m_info;
protected:
	CInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CInfoView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CInfoView)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOVIEW_H__9A1BF4A1_6A86_49F6_AD15_79A3B501B98A__INCLUDED_)
