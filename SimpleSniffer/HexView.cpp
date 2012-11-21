// HexView.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleSniffer.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexView

IMPLEMENT_DYNCREATE(CHexView, CEditView)

CHexView::CHexView()
{
	theApp.m_editor = dynamic_cast<Hex*>(this);
}

CHexView::~CHexView()
{
}


BEGIN_MESSAGE_MAP(CHexView, CEditView)
	//{{AFX_MSG_MAP(CHexView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexView drawing

void CHexView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CHexView diagnostics

#ifdef _DEBUG
void CHexView::AssertValid() const
{
	CEditView::AssertValid();
}

void CHexView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHexView message handlers

void CHexView::ShowHexText(char *data, int len)
{
	CString result; // �洢���ս��
	CString temp; // ��ʱ�洢�м���
	int lineHead; // ���׵�ƫ��

	for(lineHead = 0; lineHead < len; lineHead += 16)
	{
		// ��ӡ����ƫ��
		temp.Format("%04X: ", lineHead);
		result += temp;

		CString hex; // һ�е�16�����ַ�����ʽ
		CString asc; // һ�е�ASCII����ʽ
		int pos; // ����ƫ��
		int lineLength = len - lineHead >= 16 ? 16 : len - lineHead; // ����Ҫ��ӡ���ֽڸ���

		for(pos = 0; pos < lineLength; ++pos)
		{
			unsigned char c = (unsigned char)data[lineHead + pos];

			// 16���Ƹ�ʽ
			if(pos != 8)
				temp.Format(" %02X", c);
			else
				temp.Format("-%02X", c);
			hex += temp;

			// ASCII��ʽ
			asc += _istprint(c) ? c : '.';
		}

		result += hex;
		if(pos < 16)
		{
			CString sPad(' ', 3 * (16 - pos));
			result += sPad;
		}
		result += "  ";
		result += asc;
		result += "\r\n";
	}

	// ��ʾ������!
	this->SetWindowText(result);
}

void CHexView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CEdit& control = this->GetEditCtrl();
	control.SetReadOnly();// �༭��ֻ��, �������ֶ�����

	// ��������Ϊ"����" �Դﵽ �ո�����ĸ�ȿ��Ч��
	this->m_Font.CreatePointFont(120, "����");
	this->SetFont(&this->m_Font, false);
}
