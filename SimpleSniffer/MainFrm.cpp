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

// 在这里创建3行1列分割窗体
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	theApp.m_control = this->GetSafeHwnd();// CMainFrame 控制线程启动和终止

	CRect rc;

    // 获取框架窗口客户区的CRect对象
    GetClientRect(&rc);

    // 创建静态分割窗口，三行一列
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

// 点击了"开始"工具栏按钮, 弹出 CDevSelector 选中设备进行抓包
void CMainFrame::OnSelectstart() 
{
	// TODO: Add your command handler code here
	CDevSelector selector;

	if(IDOK == selector.DoModal() && theApp.m_curDev)
	{
		// 打开 tmp.pcap 接收包数据
		theApp.m_dumper = pcap_dump_open(theApp.m_curDev, theApp.m_tempDumpFilePath);
		theApp.startCatch(); // 启动线程抓包了
	}
}

// 点击了"终止"工具栏按钮, pcap_breakloop 正在监听的设备
void CMainFrame::OnEndcatch() 
{
	// TODO: Add your command handler code here
	pcap_breakloop(theApp.m_curDev);
}

// 得到线程退出前发出的 WM_TEXIT 消息, 可以安全地释放各种资源了
void CMainFrame::OnTExit(int exitNum)
{
	// 关闭 网卡设备 和 dump文件
	pcap_close(theApp.m_curDev);
	if(theApp.m_dumper)
		pcap_dump_close(theApp.m_dumper);

	// 现在开始不再是"正在抓包"了
	theApp.m_iscatching = FALSE;
}

// "开始"按钮的使能控制
void CMainFrame::OnUpdateSelectstart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!theApp.m_iscatching);
}

// "终止"按钮的使能控制
void CMainFrame::OnUpdateEndcatch(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_iscatching);
}

// "保存"按钮的使能控制
void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!theApp.m_iscatching);	
}

// "另存为"按钮的使能控制
void CMainFrame::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!theApp.m_iscatching);	
}

// "打开"按钮的使能控制
void CMainFrame::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!theApp.m_iscatching);	
}
