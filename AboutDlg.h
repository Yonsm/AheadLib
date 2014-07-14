


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#pragma once
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAboutDlg 类
class CAboutDlg
{
public:
	static TCHAR m_tzStatus[64];	// 状态信息字符串

private:
	static HWND m_hWnd;				// 窗口句柄
	static BOOL m_bSplash;			// 是否以 Splash 方式显示
	static INT m_iLinkIndex;		// 当前超链接

public:
	// 显示关于对话框
	static VOID WINAPI Show(HWND hParent = NULL);

	// 以 Splash 方式显示关于对话框
	static VOID WINAPI Splash(HWND hParent = NULL, UINT uTimer = 1000);

	// 关闭窗口关于对话框
	static VOID WINAPI Close(UINT uTimer = 0);

	// 设置状态信息
	static VOID WINAPI SetStatus(PCTSTR ptzText = NULL);

private:
	// 关于对话框回调函数
	static INT_PTR CALLBACK AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// 绘制对话框
	static VOID WINAPI OnPaint();

	// 获取指定点的超链接
	static INT WINAPI GetLinkIndex(POINT ptPoint);

	// 绘制超链接
	static VOID WINAPI PaintLinks(HDC hDC);
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
