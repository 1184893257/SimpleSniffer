// DevSelector.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleSniffer.h"
#include "DevSelector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDevSelector dialog


CDevSelector::CDevSelector(CWnd* pParent /*=NULL*/)
	: CDialog(CDevSelector::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDevSelector)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDevSelector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevSelector)
	DDX_Control(pDX, IDC_DEVS, m_devsName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDevSelector, CDialog)
	//{{AFX_MSG_MAP(CDevSelector)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDevSelector message handlers

// CDevSelector 初始化的时候获取设备列表
void CDevSelector::InitWinPcap()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	char errbuf[PCAP_ERRBUF_SIZE];

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1){
		::AfxMessageBox("获取设备列表失败");
		return;
	}

	for (d = alldevs; d; d = d->next){
		this->m_devsName.AddString(d->description);
		this->m_devsArray.push_back(d);
	}

	this->UpdateData(false);

	// 默认选中第一个设备, 如果只有一个设备, 直接点确认就可以了
	this->m_devsName.SetCurSel(0);
}

// 析构的时候释放设备列表
CDevSelector::~CDevSelector()
{
	// 如果获取设备失败, m_devArray 为空, 释放就会出问题
	// 因此判断不空之后才调用 pcap_freealldevs
	if(!this->m_devsArray.empty())
		pcap_freealldevs(*(this->m_devsArray.begin()));
}

// 初始化
BOOL CDevSelector::OnInitDialog() 
{
	CDialog::OnInitDialog();

	this->InitWinPcap();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// 点击了对话框的"确定"按钮, pcap_open 选中的设备
void CDevSelector::OnOK() 
{
	char errbuf[PCAP_ERRBUF_SIZE];

	pcap_if_t *d = this->m_devsArray[this->m_devsName.GetCurSel()];
	if ((theApp.m_curDev = pcap_open(d->name, /* name of the device */
		65536,/* portion of the packet to capture , 65535 guarantees that the whole packet will be captured on all the link layers */
		PCAP_OPENFLAG_PROMISCUOUS,/* promiscuous mode */
		1000,/* read timeout */
		NULL,/* authentication on the remote machine */
		errbuf/* error buffer */)) == NULL)
	{
		::AfxMessageBox("打开适配器失败!");
		theApp.m_curDev = NULL;
		return;
	}

	CDialog::OnOK();
}
