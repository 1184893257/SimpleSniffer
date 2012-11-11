// breakloop.h : main header file for the BREAKLOOP application
//

#if !defined(AFX_BREAKLOOP_H__4160EA29_1F0B_4B55_9078_F7AB88CA6234__INCLUDED_)
#define AFX_BREAKLOOP_H__4160EA29_1F0B_4B55_9078_F7AB88CA6234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBreakloopApp:
// See breakloop.cpp for the implementation of this class
//

class CBreakloopApp : public CWinApp
{
public:
	CBreakloopApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBreakloopApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBreakloopApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BREAKLOOP_H__4160EA29_1F0B_4B55_9078_F7AB88CA6234__INCLUDED_)
