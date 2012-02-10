# Microsoft Developer Studio Project File - Name="FPAnalysis" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=FPAnalysis - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FPAnalysis.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FPAnalysis.mak" CFG="FPAnalysis - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FPAnalysis - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FPAnalysis - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FPAnalysis - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 JpegLib.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "FPAnalysis - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 JpegLib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "FPAnalysis - Win32 Release"
# Name "FPAnalysis - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\agentctlanimationnames1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlaudioobjectex1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlballoonex1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlcharacterex1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlcharacters1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlcommand1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlcommandex1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlcommandsex1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlcommandswindow1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlex1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlpropertysheet1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlrequest1.cpp
# End Source File
# Begin Source File

SOURCE=.\agentctlspeechinput1.cpp
# End Source File
# Begin Source File

SOURCE=.\AgentDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BMPFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialogs.cpp
# End Source File
# Begin Source File

SOURCE=.\dialogs1.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FPAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=.\FPAnalysis.rc
# End Source File
# Begin Source File

SOURCE=.\FPAnalysisDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\FPAnalysisView.cpp
# End Source File
# Begin Source File

SOURCE=.\GaussianPage.cpp
# End Source File
# Begin Source File

SOURCE=.\HistogramPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Image.cpp
# End Source File
# Begin Source File

SOURCE=.\imgedit.cpp
# End Source File
# Begin Source File

SOURCE=.\imgscan.cpp
# End Source File
# Begin Source File

SOURCE=.\jpegfile.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MSAgent2.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinDialog1.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\agentctlanimationnames1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlaudioobjectex1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlballoonex1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlcharacterex1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlcharacters1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlcommand1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlcommandex1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlcommandsex1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlcommandswindow1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlex1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlpropertysheet1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlrequest1.h
# End Source File
# Begin Source File

SOURCE=.\agentctlspeechinput1.h
# End Source File
# Begin Source File

SOURCE=.\AgentDlg.h
# End Source File
# Begin Source File

SOURCE=.\BMPFile.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Dialogs.h
# End Source File
# Begin Source File

SOURCE=.\dialogs1.h
# End Source File
# Begin Source File

SOURCE=.\EditDlg.h
# End Source File
# Begin Source File

SOURCE=.\FPAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\FPAnalysisDoc.h
# End Source File
# Begin Source File

SOURCE=.\FPAnalysisView.h
# End Source File
# Begin Source File

SOURCE=.\GaussianPage.h
# End Source File
# Begin Source File

SOURCE=.\HistogramPage.h
# End Source File
# Begin Source File

SOURCE=.\Image.h
# End Source File
# Begin Source File

SOURCE=.\imgedit.h
# End Source File
# Begin Source File

SOURCE=.\imgscan.h
# End Source File
# Begin Source File

SOURCE=.\jpegfile.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MSAgent2.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScanDlg.h
# End Source File
# Begin Source File

SOURCE=.\SkinDialog1.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\About.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Fingerprint.ico
# End Source File
# Begin Source File

SOURCE=.\res\FPAnalysis.ico
# End Source File
# Begin Source File

SOURCE=.\res\FPAnalysis.rc2
# End Source File
# Begin Source File

SOURCE=.\res\FPAnalysisDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Help.ico
# End Source File
# Begin Source File

SOURCE=.\res\embeded\histogram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Left.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Paint2.ico
# End Source File
# Begin Source File

SOURCE=.\res\photoshop.ico
# End Source File
# Begin Source File

SOURCE=.\res\Right.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section FPAnalysis : {F5BE8BE8-7DE6-11D0-91FE-00C04FD701A5}
# 	2:5:Class:CAgentCtlCharacters
# 	2:10:HeaderFile:agentctlcharacters1.h
# 	2:8:ImplFile:agentctlcharacters1.cpp
# End Section
# Section FPAnalysis : {8B77181C-D3EF-11D1-8500-00C04FA34A14}
# 	2:5:Class:CAgentCtlAnimationNames
# 	2:10:HeaderFile:agentctlanimationnames1.h
# 	2:8:ImplFile:agentctlanimationnames1.cpp
# End Section
# Section FPAnalysis : {F5BE8BDF-7DE6-11D0-91FE-00C04FD701A5}
# 	2:5:Class:CAgentCtlPropertySheet
# 	2:10:HeaderFile:agentctlpropertysheet1.h
# 	2:8:ImplFile:agentctlpropertysheet1.cpp
# End Section
# Section FPAnalysis : {B0913410-3B44-11D1-ACBA-00C04FD97575}
# 	2:5:Class:CAgentCtlCommandEx
# 	2:10:HeaderFile:agentctlcommandex1.h
# 	2:8:ImplFile:agentctlcommandex1.cpp
# End Section
# Section FPAnalysis : {F5BE8BE3-7DE6-11D0-91FE-00C04FD701A5}
# 	2:5:Class:CAgentCtlCommand
# 	2:10:HeaderFile:agentctlcommand1.h
# 	2:8:ImplFile:agentctlcommand1.cpp
# End Section
# Section FPAnalysis : {D45FD31B-5C6E-11D1-9EC1-00C04FD7081F}
# 	2:21:DefaultSinkHeaderFile:agentctlex1.h
# 	2:16:DefaultSinkClass:CAgentCtlEx
# End Section
# Section FPAnalysis : {28D4752F-CF84-11D1-834C-00A0249F0C28}
# 	2:5:Class:CGif
# 	2:10:HeaderFile:gif.h
# 	2:8:ImplFile:gif.cpp
# End Section
# Section FPAnalysis : {6D940280-9F11-11CE-83FD-02608C3EC08A}
# 	2:21:DefaultSinkHeaderFile:imgedit.h
# 	2:16:DefaultSinkClass:CImgEdit
# End Section
# Section FPAnalysis : {84926CA1-2941-101C-816F-0E6013114B7F}
# 	2:5:Class:CImgScan
# 	2:10:HeaderFile:imgscan.h
# 	2:8:ImplFile:imgscan.cpp
# End Section
# Section FPAnalysis : {6BA90C01-3910-11D1-ACB3-00C04FD97575}
# 	2:5:Class:CAgentCtlCommandsEx
# 	2:10:HeaderFile:agentctlcommandsex1.h
# 	2:8:ImplFile:agentctlcommandsex1.cpp
# End Section
# Section FPAnalysis : {84926CA0-2941-101C-816F-0E6013114B7F}
# 	2:21:DefaultSinkHeaderFile:imgscan.h
# 	2:16:DefaultSinkClass:CImgScan
# End Section
# Section FPAnalysis : {F5BE8BDD-7DE6-11D0-91FE-00C04FD701A5}
# 	2:5:Class:CAgentCtlSpeechInput
# 	2:10:HeaderFile:agentctlspeechinput1.h
# 	2:8:ImplFile:agentctlspeechinput1.cpp
# End Section
# Section FPAnalysis : {A4C46780-499F-101B-BB78-00AA00383CBB}
# 	2:5:Class:C_Collection
# 	2:10:HeaderFile:_collection.h
# 	2:8:ImplFile:_collection.cpp
# End Section
# Section FPAnalysis : {6D0ECB27-9968-11D0-AC6E-00C04FD97575}
# 	2:5:Class:CAgentCtlCommandsWindow
# 	2:10:HeaderFile:agentctlcommandswindow1.h
# 	2:8:ImplFile:agentctlcommandswindow1.cpp
# End Section
# Section FPAnalysis : {1DAB85C3-803A-11D0-AC63-00C04FD97575}
# 	2:5:Class:CAgentCtlRequest
# 	2:10:HeaderFile:agentctlrequest1.h
# 	2:8:ImplFile:agentctlrequest1.cpp
# End Section
# Section FPAnalysis : {DE8EF600-2F82-11D1-ACAC-00C04FD97575}
# 	2:5:Class:CAgentCtlCharacterEx
# 	2:10:HeaderFile:agentctlcharacterex1.h
# 	2:8:ImplFile:agentctlcharacterex1.cpp
# End Section
# Section FPAnalysis : {59888558-512E-4E8F-8BDF-E7B6D86242A6}
# 	2:5:Class:CfdImage
# 	2:10:HeaderFile:fdimage.h
# 	2:8:ImplFile:fdimage.cpp
# End Section
# Section FPAnalysis : {F5BE8BF0-7DE6-11D0-91FE-00C04FD701A5}
# 	2:5:Class:CAgentCtlAudioObjectEx
# 	2:10:HeaderFile:agentctlaudioobjectex1.h
# 	2:8:ImplFile:agentctlaudioobjectex1.cpp
# End Section
# Section FPAnalysis : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:104
# 	2:21:SplashScreenInsertKey:4.0
# End Section
# Section FPAnalysis : {28D47530-CF84-11D1-834C-00A0249F0C28}
# 	2:21:DefaultSinkHeaderFile:gif.h
# 	2:16:DefaultSinkClass:CGif
# End Section
# Section FPAnalysis : {A920DEC5-A3F6-4057-B405-70E5F1A1E1A3}
# 	2:21:DefaultSinkHeaderFile:fdimage.h
# 	2:16:DefaultSinkClass:CfdImage
# End Section
# Section FPAnalysis : {8953C11A-4005-40DE-B36B-8D4F45951A65}
# 	2:10:MSAgent2.h:MSAgent2.h
# 	2:15:CLASS: CMSAgent:CMSAgent
# 	2:12:MSAgent2.cpp:MSAgent2.cpp
# 	2:19:Application Include:FPAnalysis.h
# End Section
# Section FPAnalysis : {8563FF20-8ECC-11D1-B9B4-00C04FD97575}
# 	2:5:Class:CAgentCtlEx
# 	2:10:HeaderFile:agentctlex1.h
# 	2:8:ImplFile:agentctlex1.cpp
# End Section
# Section FPAnalysis : {6D940281-9F11-11CE-83FD-02608C3EC08A}
# 	2:5:Class:CImgEdit
# 	2:10:HeaderFile:imgedit.h
# 	2:8:ImplFile:imgedit.cpp
# End Section
# Section FPAnalysis : {822DB1C0-8879-11D1-9EC6-00C04FD7081F}
# 	2:5:Class:CAgentCtlBalloonEx
# 	2:10:HeaderFile:agentctlballoonex1.h
# 	2:8:ImplFile:agentctlballoonex1.cpp
# End Section
