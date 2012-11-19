// SimpleSnifferDoc.cpp : implementation of the CSimpleSnifferDoc class
//

#include "stdafx.h"
#include "SimpleSniffer.h"

#include "SimpleSnifferDoc.h"

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
	// TODO: add one-time construction code here

}

CSimpleSnifferDoc::~CSimpleSnifferDoc()
{
}

BOOL CSimpleSnifferDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSimpleSnifferDoc serialization

void CSimpleSnifferDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
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
