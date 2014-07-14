


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#pragma once
#include "Define.h"
#include "Macro.h"
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CIni 类
class CIni
{
private:
	// INI 文件名
	static TCHAR m_tzFileName[MAX_PATH];

public:
	// 设置 INI 文件名
	inline static VOID WINAPI SetIniName()
	{
		GetModuleFileName(NULL, m_tzFileName, MAX_PATH);
		lstrcpy(_StrEnd(m_tzFileName) - _LengthOf(EXT_Ini), EXT_Ini);
	}

	// 设置 INI 文件名
	inline static VOID WINAPI SetIniName(PCTSTR ptzFileName)
	{
		_StrToStr(m_tzFileName, ptzFileName);
	}

	// 获取整数
	inline static UINT WINAPI GetInt(PCTSTR ptzKeyName, INT iDefault = 0, PCTSTR ptzSectionName = INI_Main)
	{
		return GetPrivateProfileInt(ptzSectionName, ptzKeyName, iDefault, m_tzFileName);
	}

	// 设置整数
	inline static BOOL WINAPI SetInt(PCTSTR ptzKeyName, INT iValue = 0, PCTSTR ptzSectionName = INI_Main)
	{
		TCHAR tzString[16];

		wsprintf(tzString, TEXT("%d"), iValue);
		return WritePrivateProfileString(ptzSectionName, ptzKeyName, tzString, m_tzFileName);
	}

	// 获取字符串
	inline static DWORD WINAPI GetString(PCTSTR ptzKeyName, PTSTR ptzReturnedString,
		DWORD dwSize = MAX_PATH, PCTSTR ptzDefault = NULL, PCTSTR ptzSectionName = INI_Main)
	{
		return GetPrivateProfileString(ptzSectionName, ptzKeyName, ptzDefault, ptzReturnedString,
			dwSize, m_tzFileName);
	}

	// 设置字符串
	inline static BOOL WINAPI SetString(PCTSTR ptzKeyName, PCTSTR ptzString = NULL, PCTSTR ptzSectionName = INI_Main)
	{
		return WritePrivateProfileString(ptzSectionName, ptzKeyName, ptzString, m_tzFileName);
	}

	// 获取结构
	inline static BOOL WINAPI GetStruct(PCTSTR ptzKeyName, PVOID pvStruct, UINT uSize, PCTSTR ptzSectionName = INI_Main)
	{
		return GetPrivateProfileStruct(ptzSectionName, ptzKeyName, pvStruct, uSize, m_tzFileName);
	}

	// 设置结构
	inline static BOOL WINAPI SetStruct(PCTSTR ptzKeyName, PVOID pvStruct, UINT uSize, PCTSTR ptzSectionName = INI_Main)
	{
		return WritePrivateProfileStruct(ptzSectionName, ptzKeyName, pvStruct, uSize, m_tzFileName);
	}

	// 获取节
	inline static DWORD WINAPI GetSection(PTSTR ptzReturnBuffer, DWORD dwSize, PCTSTR ptzSectionName = INI_Main)
	{
		return GetPrivateProfileSection(ptzSectionName, ptzReturnBuffer, dwSize, m_tzFileName);
	}

	// 设置节
	inline static DWORD WINAPI SetSection(PCTSTR ptzString, PCTSTR ptzSectionName = INI_Main)
	{
		return WritePrivateProfileSection(ptzSectionName, ptzString, m_tzFileName);
	}

	// 获取节名
	inline static DWORD WINAPI GetSectionNames(PTSTR ptzReturnBuffer, DWORD dwSize)
	{
		return GetPrivateProfileSectionNames(ptzReturnBuffer, dwSize, m_tzFileName);
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
