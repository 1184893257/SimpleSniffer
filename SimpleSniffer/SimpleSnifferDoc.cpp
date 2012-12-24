// SimpleSnifferDoc.cpp : implementation of the CSimpleSnifferDoc class
//

#include "stdafx.h"
#include "SimpleSniffer.h"

#include "SimpleSnifferDoc.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferDoc

IMPLEMENT_DYNCREATE(CSimpleSnifferDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimpleSnifferDoc, CDocument)
	//{{AFX_MSG_MAP(CSimpleSnifferDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferDoc construction/destruction

CSimpleSnifferDoc::CSimpleSnifferDoc()
{
}

CSimpleSnifferDoc::~CSimpleSnifferDoc()
{
}

BOOL CSimpleSnifferDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

// 将 src 文件的内容复制到 dest 文件
void copyFile(CFile *src, CFile *dest)
{
	char buf[1024];
	int n;

	while((n = src->Read(buf, sizeof(buf))) > 0)
		dest->Write(buf, n);
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferDoc serialization

//串行化中实现 保存/打开 逻辑
void CSimpleSnifferDoc::Serialize(CArchive& ar)
{
	CFile *f = ar.GetFile();

	// 如果是 tmp.pcap, 报错
	if(theApp.m_tempDumpFilePath.Compare(f->GetFilePath()) == 0)
	{
		CString s;
		s.Format("%s 文件用于存储当前抓到的包, 不作他用!", theApp.m_tempDumpFilePath);
		::AfxMessageBox(s);
		return;
	}

	// 如果是保存, 将 tmp.pcap 中的内容复制到 f 中
	if (ar.IsStoring())
	{
		CFile src(theApp.m_tempDumpFilePath, CFile::modeRead);
		copyFile(&src, f);
		src.Close();
	}

	// 如果是打开, 将该文件中的内容复制到 tmp.pcap, 启动线程从 tmp.pcap 读取包
	else
	{
		// 复制到 tmp.pcap
		CFile dest(theApp.m_tempDumpFilePath, CFile::modeWrite | CFile::modeCreate);
		copyFile(f, &dest);
		dest.Close();

		// 打开 tmp.pcap, 侦听, TExit 事件中关闭 tmp.pcap 文件
		FILE *fp = fopen(theApp.m_tempDumpFilePath, "rb");
		char errbuf[PCAP_ERRBUF_SIZE];
		theApp.m_curDev = pcap_fopen_offline(fp, errbuf);
		theApp.m_dumper = NULL;
		theApp.startCatch(); // 开始抓包, 还设置"正在抓包"标志
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferDoc diagnostics

#ifdef _DEBUG
void CSimpleSnifferDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimpleSnifferDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferDoc commands
