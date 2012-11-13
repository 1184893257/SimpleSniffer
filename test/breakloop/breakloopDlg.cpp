// breakloopDlg.cpp : implementation file
//

#include "stdafx.h"
#include "breakloop.h"
#include "breakloopDlg.h"
#include "thread.h"

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
// CBreakloopDlg dialog

CBreakloopDlg::CBreakloopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBreakloopDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBreakloopDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBreakloopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBreakloopDlg)
	DDX_Control(pDX, IDC_INFO, m_InfoList);
	DDX_Control(pDX, IDC_DEVS, m_DevList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBreakloopDlg, CDialog)
	//{{AFX_MSG_MAP(CBreakloopDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_MESSAGE(WM_TCATCH, OnTCatch)
	ON_MESSAGE(WM_TEXIT, OnTExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBreakloopDlg message handlers

BOOL CBreakloopDlg::OnInitDialog()
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
	this->initWinPcap();
	this->GetDlgItem(IDC_START)->EnableWindow(true);
	this->GetDlgItem(IDC_STOP)->EnableWindow(false);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBreakloopDlg::initWinPcap()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	char errbuf[PCAP_ERRBUF_SIZE];
	
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1){
		::AfxMessageBox("获取设备列表失败");
		return;
	}
	
	for (d = alldevs; d; d = d->next){
		this->m_DevList.AddString(d->description);
		this->devArray.push_back(d);
	}

	this->UpdateData(false);
}

CBreakloopDlg::~CBreakloopDlg()
{
	pcap_freealldevs(this->devArray[0]);
}

void CBreakloopDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBreakloopDlg::OnPaint() 
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
HCURSOR CBreakloopDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBreakloopDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	char errbuf[PCAP_ERRBUF_SIZE];

	pcap_if_t *d = this->devArray[this->m_DevList.GetCurSel()];

	if ((this->cur_pcap_t = pcap_open(d->name, /* name of the device */
		65536,/* portion of the packet to capture , 65535 guarantees that the whole packet will be captured on all the link layers */
		PCAP_OPENFLAG_PROMISCUOUS,/* promiscuous mode */
		1000,/* read timeout */
		NULL,/* authentication on the remote machine */
		errbuf/* error buffer */)) == NULL)
	{
		::AfxMessageBox("打开适配器失败!");
		return;
	}
	::AfxBeginThread(ThreadProc, this->cur_pcap_t);

	this->GetDlgItem(IDC_START)->EnableWindow(false);
	this->GetDlgItem(IDC_STOP)->EnableWindow(true);
}

void CBreakloopDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	pcap_breakloop(cur_pcap_t);
}

void CBreakloopDlg::OnTCatch(const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	struct tm *ltime;
	char timestr[16];
	
	/* convert the timestamp to readable format */
	ltime = localtime(&header->ts.tv_sec);
	strftime(timestr, sizeof(timestr), "%H:%M:%S", ltime);

	CString s;
	s.Format("%s, %.6d len:%d\n", timestr, header->ts.tv_usec, header->len);

	this->m_InfoList.AddString(s);
}

void CBreakloopDlg::OnTExit(int exitNum)
{
	CString s;
	s.Format("线程退出了:%d", exitNum);
	::AfxMessageBox(s);

	this->GetDlgItem(IDC_START)->EnableWindow(true);
	this->GetDlgItem(IDC_STOP)->EnableWindow(false);
}
