// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"

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
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	m_client_name = _T("localhost");
	m_send_info = _T(" ");
	m_server_name = _T("localhost");
	m_nPort = 800;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_RECEIVED_INFO, m_ctlRecvd);
	DDX_Text(pDX, IDC_CLIENT_NAME, m_client_name);
	DDX_Text(pDX, IDC_SEND_INFO, m_send_info);
	DDX_Text(pDX, IDC_SERVER_NAME, m_server_name);
	DDX_Text(pDX, IDC_SERVER_PORT, m_nPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_MESSAGE(RE_RECEIVED, OnmyReceive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
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
	this->GetDlgItem(IDC_CONNECT)->EnableWindow(true);
	this->GetDlgItem(IDC_SEND)->EnableWindow(false);
	this->GetDlgItem(IDC_CLOSE)->EnableWindow(false);
	this->GetDlgItem(IDC_SERVER_PORT)->EnableWindow(true);
	this->GetDlgItem(IDC_CLIENT_NAME)->EnableWindow(true);
	this->GetDlgItem(IDC_SERVER_NAME)->EnableWindow(true);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint() 
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(!(this->sockClient).Create())
	{
		::AfxMessageBox("生产 Socket 失败");
		::PostQuitMessage(0);
	}
	if(!(this->sockClient).Connect(this->m_server_name,this->m_nPort))
	{
		MessageBox("连接失败");
		return;
	}
	this->GetDlgItem(IDC_CONNECT)->EnableWindow(false);
	this->GetDlgItem(IDC_SEND)->EnableWindow(true);
	this->GetDlgItem(IDC_CLOSE)->EnableWindow(true);
	this->GetDlgItem(IDC_SERVER_PORT)->EnableWindow(false);
	this->GetDlgItem(IDC_CLIENT_NAME)->EnableWindow(false);
	this->GetDlgItem(IDC_SERVER_NAME)->EnableWindow(false);
}

void CClientDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	(this->sockClient).Close();
	this->GetDlgItem(IDC_CONNECT)->EnableWindow(true);
	this->GetDlgItem(IDC_SEND)->EnableWindow(false);
	this->GetDlgItem(IDC_CLOSE)->EnableWindow(false);
	this->GetDlgItem(IDC_SERVER_PORT)->EnableWindow(true);
	this->GetDlgItem(IDC_CLIENT_NAME)->EnableWindow(true);
	this->GetDlgItem(IDC_SERVER_NAME)->EnableWindow(true);
}

void CClientDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(true);

	_DATA data;
	strcpy(data.name,this->m_client_name);
	strcpy(data.data,this->m_send_info);
	int iSent=this->sockClient.Send(&data,sizeof(_DATA));
	if(iSent!=SOCKET_ERROR)
	{
		this->m_ctlRecvd.AddString(m_send_info);
		this->UpdateData(false);
	}
}

LRESULT CClientDlg::OnmyReceive(WPARAM wparam, LPARAM lParam)
{
	_DATA *data=(_DATA*)wparam;
	CString str;
	str += data->name;
	str += ":";
	str += data->data;
	this->m_ctlRecvd.AddString(str);
	this->UpdateData(false);
	return 1;
}
