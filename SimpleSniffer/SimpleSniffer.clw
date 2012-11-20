; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSimpleSnifferView
LastTemplate=CEditView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SimpleSniffer.h"
LastPage=0

ClassCount=7
Class1=CSimpleSnifferApp
Class2=CSimpleSnifferDoc
Class3=CSimpleSnifferView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_SIMPLESNIFFER_FORM
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CInfoView
Class7=CHexView
Resource3=IDR_MAINFRAME

[CLS:CSimpleSnifferApp]
Type=0
HeaderFile=SimpleSniffer.h
ImplementationFile=SimpleSniffer.cpp
Filter=N

[CLS:CSimpleSnifferDoc]
Type=0
HeaderFile=SimpleSnifferDoc.h
ImplementationFile=SimpleSnifferDoc.cpp
Filter=N

[CLS:CSimpleSnifferView]
Type=0
HeaderFile=SimpleSnifferView.h
ImplementationFile=SimpleSnifferView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_DEVS


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=SimpleSniffer.cpp
ImplementationFile=SimpleSniffer.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_SIMPLESNIFFER_FORM]
Type=1
Class=CSimpleSnifferView
ControlCount=3
Control1=IDC_START,button,1342242816
Control2=IDC_STOP,button,1342242816
Control3=IDC_DEVS,combobox,1344339970

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:CInfoView]
Type=0
HeaderFile=InfoView.h
ImplementationFile=InfoView.cpp
BaseClass=CListView
Filter=C

[CLS:CHexView]
Type=0
HeaderFile=HexView.h
ImplementationFile=HexView.cpp
BaseClass=CEditView
Filter=C
LastObject=CHexView

