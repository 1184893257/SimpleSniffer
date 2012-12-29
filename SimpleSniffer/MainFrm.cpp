// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SimpleSniffer.h"

#include "MainFrm.h"
#include "InfoView.h"
#include "HexView.h"
#include "PackInfo.h"
#include "DevSelector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SELECTSTART, OnSelectstart)
	ON_COMMAND(ID_ENDCATCH, OnEndcatch)
	ON_UPDATE_COMMAND_UI(ID_SELECTSTART, OnUpdateSelectstart)
	ON_UPDATE_COMMAND_UI(ID_ENDCATCH, OnUpdateEndcatch)
	ON_MESSAGE(WM_TEXIT, OnTExit)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

// �����ﴴ��3��1�зָ��
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	theApp.m_control = this->GetSafeHwnd();// CMainFrame �����߳���������ֹ

	CRect rc;

    // ��ȡ��ܴ��ڿͻ�����CRect����
    GetClientRect(&rc);

    // ������̬�ָ�ڣ�����һ��
    if (!m_wndSplitter.CreateStatic(this, 3, 1, WS_CHILD | WS_VISIBLE))
        return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CInfoView), CSize(rc.Width(), rc.Height()/3), pContext))
        return FALSE;
	if (!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CPackInfo), CSize(rc.Width(), rc.Height()/4), pContext))
        return FALSE;
    if (!m_wndSplitter.CreateView(2, 0, RUNTIME_CLASS(CHexView), CSize(rc.Width(), rc.Height()/2), pContext))
        return FALSE;

    return TRUE;
}

// �����"��ʼ"��������ť, ���� CDevSelector ѡ���豸����ץ��
void CMainFrame::OnSelectstart() 
{
	// TODO: Add your command handler code here
	CDevSelector selector;

	if(IDOK == selector.DoModal() && theApp.m_curDev)
	{
		// �� tmp.pcap ���հ�����
		theApp.m_dumper = pcap_dump_open(theApp.m_curDev, theApp.m_tempDumpFilePath);
		theApp.startCatch(); // �����߳�ץ����
	}
}

// �����"��ֹ"��������ť, pcap_breakloop ���ڼ������豸
void CMainFrame::OnEndcatch() 
{
	// TODO: Add your command handler code here
	pcap_breakloop(theApp.m_curDev);
}

// �õ��߳��˳�ǰ������ WM_TEXIT ��Ϣ, ���԰�ȫ���ͷŸ�����Դ��
void CMainFrame::OnTExit(int exitNum)
{
	// �ر� �����豸 �� dump�ļ�
	pcap_close(theApp.m_curDev);
	if(theApp.m_dumper)
		pcap_dump_close(theApp.m_dumper);

	// ���ڿ�ʼ������"����ץ��"��
	theApp.m_iscatching = FALSE;
}

// "��ʼ"��ť��ʹ�ܿ���
void CMainFrame::OnUpdateSelectstart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!theApp.m_iscatching);
}

// "��ֹ"��ť��ʹ�ܿ���
void CMainFrame::OnUpdateEndcatch(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_iscatching);
}

// "����"��ť��ʹ�ܿ���
void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!theApp.m_iscatching);	
}

// "���Ϊ"��ť��ʹ�ܿ���
void CMainFrame::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!theApp.m_iscatching);	
}

// "��"��ť��ʹ�ܿ���
void CMainFrame::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!theApp.m_iscatching);	
}
