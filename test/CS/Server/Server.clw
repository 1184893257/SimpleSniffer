; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServerDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Server.h"

ClassCount=5
Class1=CServerApp
Class2=CServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CRWSock
Class4=CLSock
Resource3=IDD_SERVER_DIALOG

[CLS:CServerApp]
Type=0
HeaderFile=Server.h
ImplementationFile=Server.cpp
Filter=N
LastObject=CServerApp

[CLS:CServerDlg]
Type=0
HeaderFile=ServerDlg.h
ImplementationFile=ServerDlg.cpp
Filter=D
LastObject=IDC_SEND
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ServerDlg.h
ImplementationFile=ServerDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SERVER_DIALOG]
Type=1
Class=CServerDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_START,button,1342242816
Control5=IDC_CLOSE,button,1342242816
Control6=IDC_SEND,button,1342242816
Control7=IDC_HISTORY,listbox,1352728843
Control8=IDC_SEND_INFO,edit,1350635652
Control9=IDC_PORT,edit,1350631552
Control10=IDC_NAME,edit,1350631552

[CLS:CLSock]
Type=0
HeaderFile=LSock.h
ImplementationFile=LSock.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CLSock

[CLS:CRWSock]
Type=0
HeaderFile=LSock.h
ImplementationFile=LSock.cpp
BaseClass=CSocket
Filter=N
LastObject=CRWSock
VirtualFilter=uq

