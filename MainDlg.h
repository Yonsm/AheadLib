


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#pragma once
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMainDlg 类
class CMainDlg
{
public:
	static HWND m_hWnd;			// 对话框句柄

private:
	static BOOL m_bShowOptions;	// 是否显示选项

public:
	// 显示对话框
	inline static INT_PTR WINAPI Show(HINSTANCE hInstance, PCTSTR ptzCmdLine = NULL)
	{
		return DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_Main), NULL, MainDlgProc, (LPARAM) ptzCmdLine);
	}

private:
	// 回调函数
	static INT_PTR CALLBACK MainDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// 初始化
	static VOID WINAPI OnInitDialog(LPARAM lParam);

	// 命令处理
	static VOID WINAPI OnCommand(WPARAM wParam);

	// 系统命令处理
	static VOID WINAPI OnSysCommand(WPARAM wParam);

	// 大小改变
	static VOID WINAPI OnSize(WPARAM wParam, LPARAM lParam);

	// 关闭
	static VOID WINAPI OnClose();

	// 显示隐藏选项
	static VOID WINAPI OnOptions();

	// 浏览文件
	static VOID WINAPI OnBrowse(BOOL bDllFile);

	// 消息框
	inline static INT WINAPI MsgBox(PCTSTR ptzText = NULL, UINT uType = MB_ICONINFORMATION)
	{
		return MessageBox(m_hWnd, ptzText, STR_AppName, uType);
	}

	// 错误框
	inline static INT WINAPI ErrorBox(PCTSTR ptzText = NULL)
	{
		return MsgBox(ptzText, MB_ICONSTOP);
	}

	// 居中窗口
	inline static BOOL WINAPI CenterWindow(INT iWidth, INT iHeight)
	{
		return MoveWindow(m_hWnd,
			(GetSystemMetrics(SM_CXSCREEN) - iWidth) / 2,
			(GetSystemMetrics(SM_CYSCREEN) - iHeight) / 2,
			iWidth, iHeight, TRUE);
	}

	// 拖动文件
	inline static VOID WINAPI OnDropFiles(WPARAM wParam)
	{
		TCHAR tzFileName[MAX_PATH];
		DragQueryFile((HDROP) wParam, 0, tzFileName, MAX_PATH);
		DragFinish((HDROP) wParam);
		SetDlgItemText(m_hWnd, IDC_DllFile, tzFileName);
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
