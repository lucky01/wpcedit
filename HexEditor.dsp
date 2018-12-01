# Microsoft Developer Studio Project File - Name="HexEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HexEditor - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HexEditor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HexEditor.mak" CFG="HexEditor - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HexEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
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
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/WPCEdit.exe"
# Begin Target

# Name "HexEditor - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutLimitations.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGEditData.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGInsertData.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\DMD.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEditor.rc
# End Source File
# Begin Source File

SOURCE=.\HexEditorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEditorView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyButton.cpp
# End Source File
# Begin Source File

SOURCE=.\Nag.cpp
# End Source File
# Begin Source File

SOURCE=.\NagDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Splasher.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutLimitations.h
# End Source File
# Begin Source File

SOURCE=.\Defines.h
# End Source File
# Begin Source File

SOURCE=.\DLGEditData.h
# End Source File
# Begin Source File

SOURCE=.\DLGInsertData.h
# End Source File
# Begin Source File

SOURCE=.\DLGProgress.h
# End Source File
# Begin Source File

SOURCE=.\DMD.h
# End Source File
# Begin Source File

SOURCE=.\HexEditor.h
# End Source File
# Begin Source File

SOURCE=.\HexEditorDoc.h
# End Source File
# Begin Source File

SOURCE=.\HexEditorView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyButton.h
# End Source File
# Begin Source File

SOURCE=.\Nag.h
# End Source File
# Begin Source File

SOURCE=.\NagDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Splasher.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_p.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00015.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00016.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00017.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00018.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00019.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00020.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00021.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00022.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HexEditor.ico
# End Source File
# Begin Source File

SOURCE=.\res\HexEditor.rc2
# End Source File
# Begin Source File

SOURCE=.\res\HexEditorDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon16.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon17.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon18.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon19.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon20.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon21.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon22.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon23.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon24.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon25.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon26.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon27.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon28.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon29.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon30.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon31.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon32.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon33.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon34.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon35.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon36.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon37.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon38.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon39.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon40.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon41.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon42.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon43.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon44.ico
# End Source File
# Begin Source File

SOURCE=.\Splash.bmp
# End Source File
# Begin Source File

SOURCE=.\Splash2.bmp
# End Source File
# Begin Source File

SOURCE=.\Splash3.bmp
# End Source File
# Begin Source File

SOURCE=.\Splash4.bmp
# End Source File
# Begin Source File

SOURCE=.\Splash5.BMP
# End Source File
# Begin Source File

SOURCE=.\Splash7.BMP
# End Source File
# Begin Source File

SOURCE=.\Splash8.bmp
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
