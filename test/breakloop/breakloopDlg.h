// breakloopDlg.h : header file
//

#if !defined(AFX_BREAKLOOPDLG_H__C02743A7_8362_4067_AF50_065034834DBC__INCLUDED_)
#define AFX_BREAKLOOPDLG_H__C02743A7_8362_4067_AF50_065034834DBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBreakloopDlg dialog

class CBreakloopDlg : public CDialog
{
// Construction
public:
	CBreakloopDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBreakloopDlg)
	enum { IDD = IDD_BREAKLOOP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBreakloopDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBreakloopDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BREAKLOOPDLG_H__C02743A7_8362_4067_AF50_065034834DBC__INCLUDED_)
