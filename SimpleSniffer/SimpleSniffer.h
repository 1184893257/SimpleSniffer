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
#include "Thread.h"
#include <pcap.h>

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferApp:
// See SimpleSniffer.cpp for the implementation of this class
//

class CSimpleSnifferApp : public CWinApp
{
public:
	CSimpleSnifferApp();

	// 显示/控制部分
	CPackInfo *m_packInfo;	// 显示一个数据包的各层协议头的视图(CPackInfo)
	Hex *m_editor;			// 以十六进制格式显示一个数据包的视图(CHexView)
	HWND m_control;			// 接收线程退出的消息的句柄(CMainFrame的句柄)
	HWND m_display;			// 接收抓到包的消息的句柄(CInfoView的句柄)

	// 用于抓包过程的各种数据/函数
	pcap_t *m_curDev;			// 当前 pcap_loop 监听的设备
	pcap_dumper_t *m_dumper;	// 用于存储 dump 信息
	CString m_tempDumpFilePath;	// tmp.pcap 的全路径(dump信息存到这个文件中)
	BOOL m_iscatching;			// 正在抓包? 用于设置各按钮的状态
	void startCatch();			// 启动线程抓包, 并设置"正在抓包"标志

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
