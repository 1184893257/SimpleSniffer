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

// �� src �ļ������ݸ��Ƶ� dest �ļ�
void copyFile(CFile *src, CFile *dest)
{
	char buf[1024];
	int n;

	while((n = src->Read(buf, sizeof(buf))) > 0)
		dest->Write(buf, n);
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferDoc serialization

//���л���ʵ�� ����/�� �߼�
void CSimpleSnifferDoc::Serialize(CArchive& ar)
{
	CFile *f = ar.GetFile();

	// ����� tmp.pcap, ����
	if(theApp.m_tempDumpFilePath.Compare(f->GetFilePath()) == 0)
	{
		CString s;
		s.Format("%s �ļ����ڴ洢��ǰץ���İ�, ��������!", theApp.m_tempDumpFilePath);
		::AfxMessageBox(s);
		return;
	}

	// ����Ǳ���, �� tmp.pcap �е����ݸ��Ƶ� f ��
	if (ar.IsStoring())
	{
		CFile src(theApp.m_tempDumpFilePath, CFile::modeRead);
		copyFile(&src, f);
		src.Close();
	}

	// ����Ǵ�, �����ļ��е����ݸ��Ƶ� tmp.pcap, �����̴߳� tmp.pcap ��ȡ��
	else
	{
		// ���Ƶ� tmp.pcap
		CFile dest(theApp.m_tempDumpFilePath, CFile::modeWrite | CFile::modeCreate);
		copyFile(f, &dest);
		dest.Close();

		// �� tmp.pcap, ����, TExit �¼��йر� tmp.pcap �ļ�
		FILE *fp = fopen(theApp.m_tempDumpFilePath, "rb");
		char errbuf[PCAP_ERRBUF_SIZE];
		theApp.m_curDev = pcap_fopen_offline(fp, errbuf);
		theApp.m_dumper = NULL;
		theApp.startCatch(); // ��ʼץ��, ������"����ץ��"��־
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
