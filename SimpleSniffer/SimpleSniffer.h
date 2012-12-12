// SimpleSniffer.h : main header file for the SIMPLESNIFFER application
//

#if !defined(AFX_SIMPLESNIFFER_H__3322FDE1_C733_4300_8260_9CEF79018DBD__INCLUDED_)
#define AFX_SIMPLESNIFFER_H__3322FDE1_C733_4300_8260_9CEF79018DBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "Hex.h"
#include "PackInfo.h"
#include <pcap.h>

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferApp:
// See SimpleSniffer.cpp for the implementation of this class
//

class CSimpleSnifferApp : public CWinApp
{
public:
	CSimpleSnifferApp();
	CPackInfo *m_packInfo;
	Hex *m_editor;
	HWND m_control;// �����߳��˳�����Ϣ�ľ��
	HWND m_display;// ����ץ��������Ϣ�ľ��
	pcap_t *m_curDev;	// ��ǰ pcap_loop �������豸
	CString m_tempDumpFilePath; // ��ʱ�洢 dumpfile ���ļ�·��
	pcap_dumper_t *m_dumper; // ���ڴ洢 dump ��Ϣ

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleSnifferApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSimpleSnifferApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CSimpleSnifferApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLESNIFFER_H__3322FDE1_C733_4300_8260_9CEF79018DBD__INCLUDED_)
