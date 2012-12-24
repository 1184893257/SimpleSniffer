// SimpleSniffer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SimpleSniffer.h"

#include "MainFrm.h"
#include "SimpleSnifferDoc.h"
#include "InfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferApp

BEGIN_MESSAGE_MAP(CSimpleSnifferApp, CWinApp)
	//{{AFX_MSG_MAP(CSimpleSnifferApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferApp construction

// CSimpleSnifferApp 构造的时候初始化 tmp.pcap 文件的路径, 设置"正在抓包"标志为 FALSE
CSimpleSnifferApp::CSimpleSnifferApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	char buf[1024];
	GetCurrentDirectory(sizeof(buf),buf);
	this->m_tempDumpFilePath.Format("%s\\tmp.pcap", buf);

	this->m_iscatching = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSimpleSnifferApp object

CSimpleSnifferApp theApp;
int count=1;
unsigned char m_SIP[4];
unsigned char m_DIP[4];
unsigned char m_SIPv6[16];
unsigned char m_DIPv6[16];
int ipv6=0;								//如果不是ipv6值为0 如果是值为1
int packet_kind=0;						//用于记录数据包分析到的最高层类型，0:Ethernet 1:802.3 2:ARP 3:IP 4:ICMP 5:UDP 6:IGMP 7:TCP
int remain_len;							//剩余的数据包长度，用于识别端口号为80的http

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferApp initialization

BOOL CSimpleSnifferApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSimpleSnifferDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CInfoView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

// 启动线程, 开始抓包
void CSimpleSnifferApp::startCatch()
{
	this->m_iscatching = TRUE;	// 设置"正在抓包"标志为 TRUE
	::AfxBeginThread(ThreadProc, new ThreadParam(m_curDev, m_dumper));// 启动抓包线程
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CSimpleSnifferApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferApp message handlers

