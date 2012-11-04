// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	this->m_client=NULL;
	this->m_listenSocket=NULL;
	//{{AFX_DATA_INIT(CServerDlg)
	m_Port = 800;
	m_Name = _T("lqy");
	m_SendInfo = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	DDX_Control(pDX, IDC_HISTORY, m_History);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Text(pDX, IDC_SEND_INFO, m_SendInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	this->GetDlgItem(IDC_START)->EnableWindow(true);
	this->GetDlgItem(IDC_CLOSE)->EnableWindow(false);
	this->GetDlgItem(IDC_PORT)->EnableWindow(true);
	this->GetDlgItem(IDC_NAME)->EnableWindow(true);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CServerDlg::AcceptClient()
{
	if(this->m_client)
		delete this->m_client;

	this->m_client = new CRWSock(this);
	if(!this->m_listenSocket->Accept(*this->m_client))
	{
		::AfxMessageBox("请求连接失败");
		delete this->m_client;
		this->m_client=NULL;
	}
}

void CServerDlg::ReadMessage(CRWSock *sock)
{
	_DATA data[1];
	int len=sock->Receive(data,sizeof(_DATA));
	if(len == sizeof(_DATA))
	{
		CString str;
		str += data->name;
		str += ":";
		str += data->data;
		this->m_History.AddString(str);
		this->UpdateData(false);
	}
}

void CServerDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	if(this->m_client)
		delete this->m_client;
	this->m_listenSocket->Close();
	delete this->m_listenSocket;
	
	this->GetDlgItem(IDC_START)->EnableWindow(true);
	this->GetDlgItem(IDC_CLOSE)->EnableWindow(false);
	this->GetDlgItem(IDC_PORT)->EnableWindow(true);
	this->GetDlgItem(IDC_NAME)->EnableWindow(true);
}

void CServerDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(true);
	this->m_listenSocket=new CLSock(this);
	if(!this->m_listenSocket->Create(this->m_Port))
	{
		::AfxMessageBox("创建 Socket 失败!");
		delete this->m_listenSocket;
		this->m_listenSocket=NULL;
		return;
	}

	if(!this->m_listenSocket->Listen())
	{
		::AfxMessageBox("端口设置失败!");
		delete this->m_listenSocket;
		this->m_listenSocket=NULL;
		return;
	}

	this->GetDlgItem(IDC_START)->EnableWindow(false);
	this->GetDlgItem(IDC_CLOSE)->EnableWindow(true);
	this->GetDlgItem(IDC_PORT)->EnableWindow(false);
	this->GetDlgItem(IDC_NAME)->EnableWindow(false);
}

void CServerDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(true);

	_DATA data;
	strcpy(data.name,this->m_Name);
	strcpy(data.data,this->m_SendInfo);
	int iSent=this->m_client->Send(&data,sizeof(_DATA));
	if(iSent!=SOCKET_ERROR)
	{
		this->m_History.AddString(this->m_SendInfo);
		this->UpdateData(false);
	}
}
