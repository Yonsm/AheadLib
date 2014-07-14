


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#pragma once
#include "Define.h"
#include <TChar.h>
#include <Stdio.h>
#include <Stdlib.h>
#include <String.h>
#include <CrtDbg.h>
#include <Windows.h>
#include <ShLWApi.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 错误捕捉
#define _Try
#define _Assert						_ASSERT
#define _Finally					__Finally:
#define _Leave						goto __Finally
#define _LeaveIf(c)					if (c) {_Leave;}
#define _LeaveExIf(c, e)			if (c) {e; _Leave;}
#define _ExIf(c, e)					if (c) {e;}
#define _ReturnIf(c)				if (c) {return;}
#define _ReturnExIf(c, e)			if (c) {e; return;}
#define _ReturnValIf(c, r)			if (c) {return r;}
#define _ReturnValExIf(c, e, r)		if (c) {e; return r;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 安全释放
#define _SafeDelete(p)				if (p) {delete p; p = NULL;}
#define _SafeRelease(p)				if (p) {(p)->Release(); p = NULL;}
#define _SafeFreeLibrary(h)			if (h) {FreeLibrary(h); h = NULL;}
#define _SafeDeleteObject(h)		if (h) {DeleteObject(h); h = NULL;}
#define _SafeCloseHandle(h)			if (h) {CloseHandle(h); h = NULL;}
#define _SafeDestroyWindow(h)		if (h) {DestroyWindow(h); h = NULL;}
#define _SafeCloseValidHandle(h)	if ((h) != INVALID_HANDLE_VALUE) {CloseHandle(h); h = INVALID_HANDLE_VALUE;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Windows 版本
#define _WinVer						_winver
#define _WinVerMajor				_winmajor
#define _WinVerMinor				_winminor
#define _WinVerBuild				_osver
#define _WinVerPlatform				_osplatform

#define _WinVerEqualNT()			(_WinVerPlatform == VER_PLATFORM_WIN32_NT)
#define _WinVerEqual(a, i)			((_WinVerMajor == a) && (_WinVerMinor == i))
#define _WinVerAbove(a, i)			((_WinVerMajor > a) || ((_WinVerMajor == a) && (_WinVerMinor > i)))
#define _WinVerBelow(a, i)			((_WinVerMajor < a) || ((_WinVerMajor == a) && (_WinVerMinor < i)))
#define _WinVerAboveEqual(a, i)		((_WinVerMajor > a) || ((_WinVerMajor == a) && (_WinVerMinor >= i)))
#define _WinVerBelowEqual(a, i)		((_WinVerMajor < a) || ((_WinVerMajor == a) && (_WinVerMinor <= i)))
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 常用函数简写
#define _HeapAlloc(n)				HeapAlloc(GetProcessHeap(), 0, n)
#define _HeapAllocZero(n)			HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, n)
#define _HeapFree(p)				HeapFree(GetProcessHeap(), 0, (PVOID) p)

#define _ShellOpen(f, p, s)			ShellExecute(NULL, TEXT("open"), f, p, NULL, s)

#define _CreateThread(f, p, d)		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) f, (PVOID) p, 0, (PDWORD) d)
#define _BeginThread(f, p)			{DWORD dwThread; CloseHandle(_CreateThread(f, p, &dwThread));}

#define _CreateFileForRead(f)		CreateFile(f, GENERIC_READ, 3, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL)
#define _CreateFileForWrite(f)		CreateFile(f, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL)
#define _CreateFileForAppend(f)		CreateFile(f, GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 限制数值范围
#define _Bound(v, vMin, vMax)		((v > vMax) ? vMax : ((v < vMin) ? vMin : v))

// 矩形宽度和高度
#define _RectWidth(r)				((r).right - (r).left)
#define _RectHeight(r)				((r).bottom - (r).top)
#define _SmallRectWidth(r)			((r).Right - (r).Left)
#define _SmallRectHeight(r)			((r).Bottom - (r).Top)

// DIB 计算
#define _DibAlign(w, i)				((((w * i) + 31) & ~31) / 8)
#define _DibSize(w, i, h)			(_DibAlign(w, i) * h)
#define _DibBits(p, w, i, x, y)		(p + _DibAlign(w, i) * y + x * 3)
#define _DibAlign24(w)				((w + w + w + 3) & 0xFFFFFFFC)
#define _DibSize24(w, h)			(_DibAlign24(w) * h)
#define _DibBits24(p, w, x, y)		(p + _DibAlign24(w) * y + x * 3)

// 数组元素个数
#define _NumberOf(v)				(sizeof(v) / sizeof(v[0]))
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 字符串常量的字符个数
#define _LengthOf(s)				(_NumberOf(s) - 1)

// 字符串常量的零字符位置
#define _EndOf(s)					(s + _LengthOf(s))

// 字符串占用的字节数
#define _AStrSize(a)				(lstrlenA(a) + 1)
#define _WStrSize(w)				((lstrlenW(w) + 1) * sizeof(WCHAR))
#define _StrSize(t)					((lstrlen(t) + 1) * sizeof(TCHAR))

// 字符串的零字符位置
#define _AStrEnd(a)					(a + lstrlenA(a))
#define _WStrEnd(w)					(w + lstrlenW(w))
#define _StrEnd(t)					(t + lstrlen(t))
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 字符串转换拷贝
#define _WStrToAStrN(a, w, n)		WideCharToMultiByte(CP_ACP, 0, w, -1, a, n, NULL, NULL)
#define _AStrToWStrN(w, a, n)		MultiByteToWideChar(CP_ACP, 0, a, -1, w, n)
#define _StrToStrN(t1, t2, n)		lstrcpyn(t1, t2, n)

#ifdef _UNICODE
#define _StrToAStrN(a, t, n)		_WStrToAStrN(a, t, n)
#define _StrToWStrN(w, t, n)		lstrcpyn(w, t, n)
#define _AStrToStrN(t, a, n)		_AStrToWStrN(t, a, n)
#define _WStrToStrN(t, w, n)		lstrcpyn(t, w, n)
#else // _UNICODE
#define _StrToAStrN(a, t, n)		lstrcpyn(a, t, n)
#define _StrToWStrN(w, t, n)		_AStrToWStrN(w, t, n)
#define _AStrToStrN(t, a, n)		lstrcpyn(t, a, n)
#define _WStrToStrN(t, w, n)		_WStrToAStrN(t, w, n)
#endif // _UNICODE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 字符串转换拷贝到字符数组
#define _WStrToAStr(a, w)			_WStrToAStrN(a, w, _NumberOf(a))
#define _AStrToWStr(w, a)			_AStrToWStrN(w, a, _NumberOf(w))
#define _StrToStr(t1, t2)			_StrToStrN(t1, t2, _NumberOf(t1))
#define _StrToAStr(a, t)			_StrToAStrN(a, t, _NumberOf(a))
#define _StrToWStr(w, t)			_StrToWStrN(w, t, _NumberOf(w))
#define _AStrToStr(t, a)			_AStrToStrN(t, a, _NumberOf(t))
#define _WStrToStr(t, w)			_WStrToStrN(t, w, _NumberOf(t))
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 字符串换成整数
#if (_WINVER >= 0x0410)
#define _AStrToInt(a)				StrToIntA(a)
#define _WStrToInt(w)				StrToIntW(w)
#define _StrToInt(t)				StrToInt(t)
#else // (_WINVER >= 0x0410)
#define _AStrToInt(a)				atoi(a)
#define _WStrToInt(w)				_wtoi(w)
#ifdef _UNICODE
#define _StrToInt(t)				_wtoi(t)
#else if // _UNICODE
#define _StrToInt(t)				atoi(t)
#endif // _UNICODE
#endif // (_WINVER >= 0x0410)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 字符和字符串查找
#if (_WINVER >= 0x0410)
#define _AStrStr(s1, s2)			StrStrA(s1, s2)
#define _WStrStr(w1, w2)			StrStrW(w1, w2)
#define _StrStr(t1, t2)				StrStr(t1, t2)
#define _AStrChr(a, c)				StrChrA(a, c)
#define _WStrChr(w, c)				StrChrW(w, c)
#define _StrChr(t, c)				StrChr(t, c)
#define _AStrRChr(a, c)				StrRChrA(a, NULL, c)
#define _WStrRChr(w, c)				StrRChrW(w, NULL, c)
#define _StrRChr(t, c)				StrRChr(t, NULL, c)
#else // (_WINVER >= 0x0410)
#define _AStrStr(s1, s2)			strstr(s1, s2)
#define _WStrStr(w1, w2)			wcsstr(1w, w2)
#define _AStrChr(a, c)				strchr(a, c)
#define _WStrChr(w, c)				wcschr(w, c)
#define _AStrRChr(a, c)				strrchr(a, c)
#define _WStrRChr(w, c)				wcsrchr(w, c)
#ifdef _UNICODE
#define _StrStr(t1, t2)				wcsstr(t1, t2)
#define _StrChr(t, c)				wcschr(t, c)
#define _StrRChr(t, c)				wcsrchr(t, c)
#else if // _UNICODE
#define _StrStr(t1, t2)				strstr(t1, t2)
#define _StrChr(t, c)				strchr(t, c)
#define _StrRChr(t, c)				strrchr(t, c)
#endif // _UNICODE
#endif // (_WINVER >= 0x0410)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
