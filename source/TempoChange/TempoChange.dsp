# Microsoft Developer Studio Project File - Name="CFTempoChange" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CFTempoChange - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TempoChange.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TempoChange.mak" CFG="CFTempoChange - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CFTempoChange - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CFTempoChange - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CFTempoChange - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D WINVER=0x0400 /D try=__try /D except=__except /D leave=__leave /D finally=__finally /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 strmbase.lib msvcrt.lib quartz.lib vfw32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib SoundTouch.lib bpm.lib /nologo /stack:0x200000,0x200000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /map /machine:I386 /nodefaultlib /out:"../../../Apps/Bin/Release/CFTempoChange.ax" /libpath:"..\..\lib"
# Begin Custom Build - Registering DirectShow filter $(TargetPath)
OutDir=.\Release
TargetPath=\HD\RTPipe\Apps\Bin\Release\CFTempoChange.ax
InputPath=\HD\RTPipe\Apps\Bin\Release\CFTempoChange.ax
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.time" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s "$(TargetPath)" 
	date /t > "$(OutDir)\regsvr32.time" 
	time /t >> "$(OutDir)\regsvr32.time" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CFTempoChange - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "WIN32" /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D WINVER=0x0400 /D DBG=1 /D "DEBUG" /D "_DEBUG" /D try=__try /D except=__except /D leave=__leave /D finally=__finally /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 strmbasd.lib msvcrtd.lib quartz.lib vfw32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib SoundTouchD.lib bpmD.lib /nologo /stack:0x200000,0x200000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib /out:"../../../Apps/Bin/Debug/CFTempoChange.ax" /pdbtype:sept /libpath:"..\..\lib"
# Begin Custom Build - Registering DirectShow filter $(TargetPath)
OutDir=.\Debug
TargetPath=\HD\RTPipe\Apps\Bin\Debug\CFTempoChange.ax
InputPath=\HD\RTPipe\Apps\Bin\Debug\CFTempoChange.ax
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.time" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s "$(TargetPath)" 
	date /t > "$(OutDir)\regsvr32.time" 
	time /t >> "$(OutDir)\regsvr32.time" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "CFTempoChange - Win32 Release"
# Name "CFTempoChange - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DLL.cpp
# End Source File
# Begin Source File

SOURCE=.\TempoChange.DEF
# End Source File
# Begin Source File

SOURCE=.\TempoChange.idl
# ADD MTL /h "TempoChange_i.h" /iid "TempoChange_uuid.c"
# SUBTRACT MTL /mktyplib203
# End Source File
# Begin Source File

SOURCE=.\TempoChangeFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\TempoChangeInputPin.cpp
# End Source File
# Begin Source File

SOURCE=.\TempoChangeOutputPin.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ids.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\TempoChangeFilter.h
# End Source File
# Begin Source File

SOURCE=.\TempoChangeInputPin.h
# End Source File
# Begin Source File

SOURCE=.\TempoChangeOutputPin.h
# End Source File
# Begin Source File

SOURCE=.\ver.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\TempoChange.rc
# End Source File
# Begin Source File

SOURCE=.\TempoChange.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\README.TXT
# End Source File
# End Target
# End Project
