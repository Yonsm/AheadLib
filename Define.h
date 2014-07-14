


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#pragma once


#define _CHS
#define _WINVER					0x0400

#if (_WINVER >= 0x0500)
#define UNICODE
#define _UNICODE
#endif

#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 程序信息
#define VER_Major				2
#define VER_Minor				2
#define VER_Release				150 
#define VER_Build				650  
#define VER_Version				MAKELONG(MAKEWORD(VER_Major, VER_Minor), VER_Release)

#define _Stringizing(v)			#v
#define _VerJoin(a, b, c, d)	_Stringizing(a.b.c.d)

#define STR_BuildDate			TEXT(__DATE__)
#define STR_BuildTime			TEXT(__TIME__)
#define STR_BuilDateTime		TEXT(__DATE__) TEXT(" ") TEXT(__TIME__)
#define STR_Version				TEXT(_VerJoin(VER_Major, VER_Minor, VER_Release, VER_Build))

#define STR_AppName				TEXT("AheadLib")
#define STR_Author				TEXT("Yonsm")
#define STR_Corporation			TEXT("Yonsm.com")
#define STR_Web					TEXT("www.luocong.com/bbs")
#define STR_Email				TEXT("Yonsm@163.com")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 扩展名
#define EXT_Chm					TEXT(".chm")
#define EXT_Dll					TEXT(".dll")
#define EXT_Exe					TEXT(".exe")
#define EXT_Ini					TEXT(".ini")
#define EXT_Cpp					TEXT(".cpp")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INI 键名
#define INI_Main				STR_AppName
#define INI_WindowLeft			TEXT("WindowLeft")
#define INI_WindowTop			TEXT("WindowTop")
#define INI_WindowWidth			TEXT("WindowWidth")
#define INI_WindowHeight		TEXT("WindowHeight")
#define INI_WindowState			TEXT("WindowState")
#define INI_ShowSplash			TEXT("ShowSplash")

#define INI_ShowOptions			TEXT("ShowOptions")
#define INI_CallRedirect		TEXT("CallRedirect")
#define INI_LoadIfNeed			TEXT("LoadIfNeed")
#define INI_JumpToOrign			TEXT("JumpToOrign")
#define INI_MultiThread			TEXT("MultiThread")
#define INI_SystemPath			TEXT("SystemPath")
#define INI_GenerateHook		TEXT("GenerateHook")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 常规字符串
#define	STR_CheckUpdate			TEXT("检查更新")
#define	STR_VisitWeb			TEXT("访问网站")
#define	STR_WriteEmail			TEXT("写信给作者")

#define STR_CheckUpdateTip		TEXT("在 Internet 上检查软件更新信息")
#define STR_VisitWebTip			TEXT("访问 ") STR_Web
#define STR_WriteEmailTip		TEXT("写信到 ") STR_Email

#define STR_VisitWebUrl			TEXT("http://") STR_Web
#define STR_WriteEmailUrl		TEXT("mailto:") STR_Email TEXT("?Subject=") STR_AppName

#define STR_VersionStamp		TEXT("版本: ") STR_Version
#define STR_BuildStamp			TEXT("编译: ") STR_BuilDateTime
#define STR_Description			TEXT("方便快捷地生成 Trojan DLL 代码。")
#define STR_Copyright			TEXT("版权所有 (C) 2004 ") STR_Corporation TEXT("，保留所有权利。")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文件扩展名过滤器
#define FILTER_All				TEXT("所有文件(*.*)\0*.*\0")
#define FILTER_Dll				TEXT("DLL 文件(*.dll)\0*.dll\0")
#define FILTER_Cpp				TEXT("CPP 文件(*.cpp)\0*.cpp\0")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
