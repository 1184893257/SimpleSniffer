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

// CDevSelector ��ʼ����ʱ���ȡ�豸�б�
void CDevSelector::InitWinPcap()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	char errbuf[PCAP_ERRBUF_SIZE];

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1){
		::AfxMessageBox("��ȡ�豸�б�ʧ��");
		return;
	}

	for (d = alldevs; d; d = d->next){
		this->m_devsName.AddString(d->description);
		this->m_devsArray.push_back(d);
	}

	this->UpdateData(false);

	// Ĭ��ѡ�е�һ���豸, ���ֻ��һ���豸, ֱ�ӵ�ȷ�ϾͿ�����
	this->m_devsName.SetCurSel(0);
}

// ������ʱ���ͷ��豸�б�
CDevSelector::~CDevSelector()
{
	// �����ȡ�豸ʧ��, m_devArray Ϊ��, �ͷžͻ������
	// ����жϲ���֮��ŵ��� pcap_freealldevs
	if(!this->m_devsArray.empty())
		pcap_freealldevs(*(this->m_devsArray.begin()));
}

// ��ʼ��
BOOL CDevSelector::OnInitDialog() 
{
	CDialog::OnInitDialog();

	this->InitWinPcap();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// ����˶Ի����"ȷ��"��ť, pcap_open ѡ�е��豸
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
		::AfxMessageBox("��������ʧ��!");
		theApp.m_curDev = NULL;
		return;
	}

	CDialog::OnOK();
}
