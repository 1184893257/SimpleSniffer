; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SimpleSniffer.h"
LastPage=0

ClassCount=9
Class1=CSimpleSnifferApp
Class2=CSimpleSnifferDoc
Class3=CSimpleSnifferView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDD_SELECT
Class5=CAboutDlg
Class6=CInfoView
Class7=CHexView
Class8=CPackInfo
Class9=CDevSelector
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
LastObject=CSimpleSnifferView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_FILE_OPEN




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
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_FILE_SAVE_AS
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_APP_ABOUT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
CommandCount=2

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_SELECTSTART
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_ENDCATCH
CommandCount=4

[CLS:CInfoView]
Type=0
HeaderFile=InfoView.h
ImplementationFile=InfoView.cpp
BaseClass=CListView
Filter=C
VirtualFilter=VWC
LastObject=CInfoView

[CLS:CHexView]
Type=0
HeaderFile=HexView.h
ImplementationFile=HexView.cpp
BaseClass=CEditView
Filter=C
LastObject=CHexView
VirtualFilter=VWC

[CLS:CPackInfo]
Type=0
HeaderFile=PackInfo.h
ImplementationFile=PackInfo.cpp
BaseClass=CEditView
Filter=C
VirtualFilter=VWC
LastObject=CPackInfo

[DLG:IDD_SELECT]
Type=1
Class=CDevSelector
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DEVS,combobox,1344339970

[CLS:CDevSelector]
Type=0
HeaderFile=DevSelector.h
ImplementationFile=DevSelector.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_SELECTSTART
VirtualFilter=dWC

