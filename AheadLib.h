


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#pragma once
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 结果代码
typedef enum tagALRESULT
{
	ALResult_Success,
	ALResult_NotAllRedirect,
	ALResult_InvalidArgs,
	ALResult_OpenDllFile,
	ALResult_InvalidPeFile,
	ALResult_NoExportTable,
	ALResult_HeapAlloc,
	ALResult_WriteCppFile
}
ALRESULT, *PALRESULT;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数类型
typedef enum tagEXPORTTYPE
{
	ET_NONAME,
	ET_CPP,
	ET_STD,
	ET_FAST,
	ET_CDECL
}
EXPORTTYPE, *PEXPORTTYPE;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 结果文本
const PTSTR STR_AheadLib_Result[] =
{
	TEXT("代码成功生成。"),
	TEXT("代码成功生成，但是并非所有函数都能直接转发。"),
	TEXT("参数不完整。"),
	TEXT("打开 DLL 文件错误。"),
	TEXT("无效的 PE 文件。"),
	TEXT("输入文件中不存在导出表。"),
	TEXT("无法分配内存——开玩笑！什么破机器？"),
	TEXT("无法写入到 CPP 文件中。")
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数类型
typedef DWORD (WINAPI *UNDECORATESYMBOLNAME)(PCSTR, PSTR, DWORD, DWORD);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAheadLib 类
class CAheadLib
{
public:
	static BOOL m_bCallRedirect;							// 直接转发函数
	static BOOL m_bLoadIfNeed;								// 需要时载入 DLL
	static BOOL m_bJumpToOrigin;							// 直接转跳到原始函数
	static BOOL m_bMultiThread ;							// 支持多线程
	static BOOL m_bSystemPath;								// 系统路径
	static BOOL m_bGenerateHook;							// 生成 HOOK 代码
	static TCHAR m_tzDllFile[MAX_PATH];						// 输入 DLL
	static TCHAR m_tzCppFile[MAX_PATH];						// 输出 CPP
	static CHAR m_szOriginDll[MAX_PATH];					// 原始 DLL
	static CHAR m_szOrigin[MAX_PATH];						// 原始名称

private:
	static HMODULE m_hDbgHelp;								// DbgHelp 模块句柄
	static UNDECORATESYMBOLNAME m_pUnDecorateSymbolName;	// UnDecorateSymbolName 函数指针

public:
	// 生成
	static ALRESULT WINAPI Generate(BOOL bWriteCppFile = FALSE);

	// 设置选项可用状态
	static VOID WINAPI SetOptionsEnabled();

	// 从 INI 中载入选项设置
	static VOID WINAPI LoadOptions();

	// 保存选项设置
	static VOID WINAPI SaveOptions();

	// 读取选项设置
	static VOID WINAPI GetOptions();

	// 获取结果文本
	inline static PCTSTR WINAPI GetResult(ALRESULT alResult)
	{
		return STR_AheadLib_Result[alResult];
	}

private:
	// 生成代码
	static DWORD WINAPI GenerateCode(PSTR pszBuffer, PSTR* ppszNames, DWORD dwBase, DWORD dwCount, BOOL& bLoadOrigin);

	// 生成导出指示符
	static BOOL WINAPI GenerateExport(PSTR& pszBuffer, PSTR* ppszNames, DWORD dwBase, DWORD dwCount);

	// 生成函数
	static VOID WINAPI GenerateFunction(PSTR& pszBuffer, PSTR pszName, DWORD dwBase, DWORD dwIndex);

	// 生成合法的函数名称
	static VOID WINAPI GenerateDeclaration(PSTR pszDeclaration, PSTR pszCallName, PSTR pszName, DWORD Ordinals);

	// 把 RVA 转换为文件偏移
	static DWORD WINAPI RvaToOffset(const PIMAGE_NT_HEADERS pInh, DWORD dwRva);

	// 判断导出函数类型
	static EXPORTTYPE WINAPI GetExportType(PCSTR pszName, PSTR& pAt);

	// 生成参数列表
	inline static VOID WINAPI GenerateParam(PSTR pszBuffer, INT iParamCount);

	// 生成 #pragma 导出指示符
	static VOID WINAPI PragmaExport(PSTR& pszBuffer, BOOL& bPragmaExport, DWORD Ordinals,
		PCSTR pszName = NULL, BOOL bRedirect = FALSE);

	// 写入到 CPP 文件
	static BOOL WINAPI WriteCppFile(PCSTR pszBuffer, DWORD dwSize);

	// 复制数据并移动指针
	inline static VOID WINAPI CopyString(PSTR& pszDest, PCSTR pszSrc, SIZE_T sztSize)
	{
		CopyMemory(pszDest, pszSrc, sztSize);
		pszDest += sztSize;
	}

	// 判断导出名称是否可以被转发
	inline static BOOL WINAPI CanRedirect(PCSTR pszExportName)
	{
		return pszExportName && m_bCallRedirect && IsStringLegality(pszExportName);
	}

	// 判断字符串是否为纯数字串
	inline static BOOL WINAPI IsStringNumberic(PCSTR pszString)
	{
		for (PCSTR p = pszString; *p; p++)
		{
			if ((*p < '0') || (*p > '9'))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	// 判断字符串是否为合法的函数字符串
	inline static BOOL WINAPI IsStringLegality(PCSTR pszString)
	{
		for (PCSTR p = pszString; *p; p++)
		{
			if (((*p == '_') ||
				((*p >= 'A') && (*p <= 'Z')) ||
				((*p >= 'a') && (*p <= 'z')) ||
				((*p >= '0') && (*p <= '9'))) == FALSE)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
