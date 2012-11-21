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
	CString result; // 存储最终结果
	CString temp; // 临时存储中间结果
	int lineHead; // 行首的偏移

	for(lineHead = 0; lineHead < len; lineHead += 16)
	{
		// 打印行首偏移
		temp.Format("%04X: ", lineHead);
		result += temp;

		CString hex; // 一行的16进制字符串形式
		CString asc; // 一行的ASCII码形式
		int pos; // 行内偏移
		int lineLength = len - lineHead >= 16 ? 16 : len - lineHead; // 这行要打印的字节个数

		for(pos = 0; pos < lineLength; ++pos)
		{
			unsigned char c = (unsigned char)data[lineHead + pos];

			// 16进制格式
			if(pos != 8)
				temp.Format(" %02X", c);
			else
				temp.Format("-%02X", c);
			hex += temp;

			// ASCII格式
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

	// 显示出来吧!
	this->SetWindowText(result);
}

void CHexView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CEdit& control = this->GetEditCtrl();
	control.SetReadOnly();// 编辑区只读, 不允许手动更改

	// 设置字体为"宋体" 以达到 空格与字母等宽的效果
	this->m_Font.CreatePointFont(120, "宋体");
	this->SetFont(&this->m_Font, false);
}
