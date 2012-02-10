; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1

LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FPAnalysis.h"
LastPage=0

ClassCount=15
Class1=CFPAnalysisApp
Class2=CFPAnalysisDoc
Class3=CFPAnalysisView
Class4=CMainFrame

ResourceCount=14
Resource1=IDD_CONVOLUTION
Resource2=IDR_MAINFRAME
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDR_FPANALTYPE

Class7=CProgressDlg
Resource4=CG_IDD_PROGRESS
Class8=CConvolutionDlg
Resource5=IDD_WIZP1HISTOGRAM
Class9=CImageInfoDlg
Resource6=IDD_FINGERDATA
Class10=CScanDlg
Class11=CSplashWnd
Resource7=IDD_ABOUTBOX
Resource8=IDD_BITMAPINFO
Resource9=IDD_SCAN
Resource10=IDD_AGENT_DIALOG
LastClass=CFPAnalysisView
Class12=CModelessDlg
Resource11=IDD_SKINDIALOG_DIALOG
Class13=CAgentDlg
Resource12=IDD_DUMMY
Resource13=IDD_DISPLAY
Class14=CHistogramPage
Class15=CGaussianPage
Resource14=IDD_WIZP2GAUSSIAN




[CLS:CFPAnalysisApp]
Type=0
HeaderFile=FPAnalysis.h
ImplementationFile=FPAnalysis.cpp
Filter=N
LastObject=CFPAnalysisApp

[CLS:CFPAnalysisDoc]
Type=0
HeaderFile=FPAnalysisDoc.h
ImplementationFile=FPAnalysisDoc.cpp
Filter=N
LastObject=CFPAnalysisDoc

[CLS:CFPAnalysisView]
Type=0
HeaderFile=FPAnalysisView.h
ImplementationFile=FPAnalysisView.cpp
Filter=T
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_ACTION_REGIONOFINTEREST


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=T
LastObject=CChildFrame
BaseClass=CMDIChildWnd
VirtualFilter=mfWC


[CLS:CAboutDlg]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
BaseClass=CDialog
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDOK,button,1342406657
Control2=IDC_STATIC,static,1342308352
Control3=IDC_CREDIT,button,1342275584
Control4=IDC_ANIGIF1,{82351441-9094-11D1-A24B-00A0C932C7DF},1342242816

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_VIEW_MODELESS
Command9=ID_APP_ABOUT
CommandCount=9

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_WINDOW_ZOOMOUT
Command10=ID_WINDOW_ZOOMIN
CommandCount=10

[MNU:IDR_FPANALTYPE]
Type=1
Class=CFPAnalysisView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_SCAN
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_SEND_MAIL
Command11=ID_FILE_MRU_FILE1
Command12=ID_APP_EXIT
Command13=ID_EDIT_UNDO
Command14=ID_EDIT_CUT
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=ID_EDIT_DATA
Command18=ID_VIEW_WIZARD
Command19=ID_VIEW_GRAY
Command20=ID_VIEW_NEGATIVE
Command21=ID_VIEW_CONVOLVE
Command22=ID_VIEW_EDGE
Command23=ID_VIEW_EQUALIZE
Command24=ID_VIEW_BLURR
Command25=ID_VIEW_NORMALIZE
Command26=ID_ACTION_REGIONOFINTEREST
Command27=ID_VIEW_ORIENTATION
Command28=ID_VIEW_SEGMENTATION
Command29=ID_VIEW_BINARY
Command30=ID_VIEW_ADAPTIVEBINARIZE
Command31=ID_VIEW_THINNING
Command32=ID_VIEW_EXTRACTION
Command33=ID_VIEW_TOOLBAR
Command34=ID_VIEW_STATUS_BAR
Command35=ID_VIEW_CORE
Command36=ID_VIEW_DOCUMENTINFO
Command37=ID_WINDOW_NEW
Command38=ID_WINDOW_CASCADE
Command39=ID_WINDOW_TILE_HORZ
Command40=ID_WINDOW_ARRANGE
Command41=ID_WINDOW_ZOOMIN
Command42=ID_WINDOW_ZOOMOUT
Command43=ID_WINDOW_FIT
Command44=ID_HELP_HELP
Command45=ID_HELP_ABOUT
CommandCount=45

[DLG:CG_IDD_PROGRESS]
Type=1
Class=CProgressDlg
ControlCount=5
Control1=IDCANCEL,button,1342242817
Control2=CG_IDC_PROGDLG_PROGRESS,msctls_progress32,1350565888
Control3=CG_IDC_PROGDLG_PERCENT,static,1342308352
Control4=IDC_ANIGIF1,{82351441-9094-11D1-A24B-00A0C932C7DF},1342242816
Control5=IDC_CAPTION,static,1342308352

[CLS:CProgressDlg]
Type=0
HeaderFile=Dialogs.h
ImplementationFile=Dialogs.cpp
BaseClass=CDialog
LastObject=CG_IDC_PROGDLG_PERCENT
Filter=D
VirtualFilter=dWC

[DLG:IDD_CONVOLUTION]
Type=1
Class=CConvolutionDlg
ControlCount=35
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1484849280
Control4=IDC_EDIT2,edit,1484849280
Control5=IDC_EDIT3,edit,1484849280
Control6=IDC_EDIT4,edit,1484849280
Control7=IDC_EDIT5,edit,1484849280
Control8=IDC_EDIT6,edit,1484849280
Control9=IDC_EDIT7,edit,1484849280
Control10=IDC_EDIT8,edit,1484849280
Control11=IDC_EDIT9,edit,1484849280
Control12=IDC_EDIT10,edit,1484849280
Control13=IDC_EDIT11,edit,1484849280
Control14=IDC_EDIT12,edit,1484849280
Control15=IDC_EDIT13,edit,1484849280
Control16=IDC_EDIT14,edit,1484849280
Control17=IDC_EDIT15,edit,1484849280
Control18=IDC_EDIT16,edit,1484849280
Control19=IDC_EDIT17,edit,1484849280
Control20=IDC_EDIT18,edit,1484849280
Control21=IDC_EDIT19,edit,1484849280
Control22=IDC_EDIT20,edit,1484849280
Control23=IDC_EDIT21,edit,1484849280
Control24=IDC_EDIT22,edit,1484849280
Control25=IDC_EDIT23,edit,1484849280
Control26=IDC_EDIT24,edit,1484849280
Control27=IDC_EDIT25,edit,1484849280
Control28=IDC_COMBO_FILTER,combobox,1344342019
Control29=IDC_STATIC,static,1342308865
Control30=IDC_SLIDER_SHARP,msctls_trackbar32,1342242840
Control31=IDC_STATIC_SHARP,static,1342308864
Control32=IDC_STATIC,static,1342308864
Control33=IDC_STATIC,static,1342177283
Control34=IDC_EDIT_HELP,edit,1344342020
Control35=IDC_STATIC,static,1342308354

[CLS:CConvolutionDlg]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
BaseClass=CDialog
Filter=D
LastObject=CConvolutionDlg
VirtualFilter=dWC

[DLG:IDD_BITMAPINFO]
Type=1
Class=CImageInfoDlg
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDC_STATIC2,static,1342308352
Control3=IDC_STATIC3,static,1342308352
Control4=IDC_STATIC4,static,1342308352
Control5=IDC_HEIGHT,static,1342308353
Control6=IDC_WIDTH,static,1342308353
Control7=IDC_BPP,static,1342308353
Control8=IDC_STATIC,static,1342308352
Control9=IDC_COMPRESSION,static,1342308353
Control10=IDC_STATIC6,static,1342308352
Control11=IDC_IMAGESIZE,static,1342308353
Control12=IDC_STATIC,static,1342308352
Control13=IDC_COLORSUSED,static,1342308353

[CLS:CImageInfoDlg]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
BaseClass=CDialog
Filter=D
LastObject=CImageInfoDlg
VirtualFilter=dWC

[DLG:IDD_SCAN]
Type=1
Class=CScanDlg
ControlCount=14
Control1=IDOK,button,1476493313
Control2=IDCANCEL,button,1342275584
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SELECTSCANNER,button,1342275584
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STARTSCANNER,button,1342275584
Control8=IDC_IMAGEPATH,edit,1350631552
Control9=IDC_BROWSE,button,1342242816
Control10=IDC_FINGERPRINTSCAN,{84926CA0-2941-101C-816F-0E6013114B7F},1342242816
Control11=IDC_IMGEDIT,{6D940280-9F11-11CE-83FD-02608C3EC08A},1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352

[CLS:CScanDlg]
Type=0
HeaderFile=ScanDlg.h
ImplementationFile=ScanDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CScanDlg
VirtualFilter=dWC

[CLS:CSplashWnd]
Type=0
HeaderFile=dialogs1.h
ImplementationFile=dialogs1.cpp
BaseClass=CWnd

[DLG:IDD_DISPLAY]
Type=1
Class=?
ControlCount=2
Control1=IDC_DISPLAY_STATIC,static,1342308352
Control2=IDOK,button,1342275584

[DLG:IDD_SKINDIALOG_DIALOG]
Type=1
Class=?
ControlCount=1
Control1=IDC_SKIN2,{0944D16C-D0F4-4389-982A-A085595A9EB3},1342242816

[DLG:IDD_FINGERDATA]
Type=1
Class=?
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_RADIO3,button,1342177289
Control6=IDC_RADIO4,button,1342177289
Control7=IDC_RADIO5,button,1342177289
Control8=IDC_RADIO6,button,1342177289
Control9=IDC_RADIO7,button,1342177289
Control10=IDC_RADIO8,button,1342177289
Control11=IDC_RADIO9,button,1342177289
Control12=IDC_RADIO10,button,1342177289
Control13=IDC_ANIGIF1,{82351441-9094-11D1-A24B-00A0C932C7DF},1342242816
Control14=IDC_ANIGIF2,{82351441-9094-11D1-A24B-00A0C932C7DF},1342242816
Control15=IDC_STATIC,button,1342177287
Control16=IDC_EDIT1,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT2,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT3,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT4,edit,1350631552
Control24=IDC_RADIO11,button,1342308361
Control25=IDC_RADIO12,button,1342177289
Control26=IDC_STATIC,button,1342177287

[DLG:IDD_DUMMY]
Type=1
Class=CModelessDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_AGENTCONTROL,{D45FD31B-5C6E-11D1-9EC1-00C04FD7081F},1342177280

[CLS:CModelessDlg]
Type=0
HeaderFile=ModelessDlg.h
ImplementationFile=ModelessDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CModelessDlg
VirtualFilter=dWC

[DLG:IDD_AGENT_DIALOG]
Type=1
Class=CAgentDlg
ControlCount=1
Control1=IDC_CONTROL1,{D45FD31B-5C6E-11D1-9EC1-00C04FD7081F},1342177280

[CLS:CAgentDlg]
Type=0
HeaderFile=AgentDlg.h
ImplementationFile=AgentDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAgentDlg
VirtualFilter=dWC

[DLG:IDD_WIZP1HISTOGRAM]
Type=1
Class=CHistogramPage
ControlCount=3
Control1=IDC_LABEL1,{978C9E23-D4B0-11CE-BF2D-00AA003F40D0},1342177280
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_STATIC,static,1342177294

[DLG:IDD_WIZP2GAUSSIAN]
Type=1
Class=CGaussianPage
ControlCount=3
Control1=IDC_LABEL1,{978C9E23-D4B0-11CE-BF2D-00AA003F40D0},1342177280
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_STATIC,static,1342177294

[CLS:CHistogramPage]
Type=0
HeaderFile=HistogramPage.h
ImplementationFile=HistogramPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CHistogramPage
VirtualFilter=idWC

[CLS:CGaussianPage]
Type=0
HeaderFile=GaussianPage.h
ImplementationFile=GaussianPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CGaussianPage
VirtualFilter=idWC

