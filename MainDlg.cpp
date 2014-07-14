


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#include "Main.h"
#include "MainDlg.h"

#pragma warning(disable:4244)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMainDlg 类静态成员变量
HWND CMainDlg::m_hWnd = NULL;			// 对话框句柄
BOOL CMainDlg::m_bShowOptions = TRUE;	// 是否显示选项
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 回调函数
INT_PTR CALLBACK CMainDlg::MainDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		// 对话框被创建
		m_hWnd = hWnd;
		OnInitDialog(lParam);
		break;

	case WM_COMMAND:
		// 命令处理
		OnCommand(wParam);
		break;

	case WM_SYSCOMMAND:
		// 系统命令处理
		OnSysCommand(wParam);
		break;

	case WM_SIZE:
		// 大小改变
		OnSize(wParam, lParam);
		break;

	case WM_DROPFILES:
		// 拖动文件
		OnDropFiles(wParam);
		break;

	case WM_CLOSE:
		// 对话框被销毁
		OnClose();
		break;
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化
VOID WINAPI CMainDlg::OnInitDialog(LPARAM lParam)
{
	UINT uTab = 16;

	// 设置图标
	SetClassLongPtr(m_hWnd, GCL_HICON, (LONG_PTR) LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_Main)));

	// 载入选项设置
	CAheadLib::LoadOptions();

	// 隐藏选项
	if (CIni::GetInt(INI_ShowOptions, TRUE) == FALSE)
	{
		OnOptions();
	}

	// 设置编辑框
	SendDlgItemMessage(m_hWnd, IDC_DllFile, EM_LIMITTEXT, MAX_PATH, 0);
	SendDlgItemMessage(m_hWnd, IDC_CppFile, EM_LIMITTEXT, MAX_PATH, 0);
	SendDlgItemMessage(m_hWnd, IDC_OriginDll, EM_LIMITTEXT, MAX_PATH, 0);
	SendDlgItemMessage(m_hWnd, IDC_Preview, EM_SETTABSTOPS, 1, (LPARAM) &uTab);
	SetDlgItemText(m_hWnd, IDC_DllFile, (PTSTR) lParam);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 命令处理
VOID WINAPI CMainDlg::OnCommand(WPARAM wParam)
{
	PSTR p;
	ALRESULT alResult;

	switch (LOWORD(wParam))
	{
	case IDOK:
		// 生成文件
		alResult = CAheadLib::Generate(TRUE);
		MsgBox(CAheadLib::GetResult(alResult), (alResult <= ALResult_NotAllRedirect) ? MB_ICONINFORMATION : MB_ICONSTOP);
		break;

	case IDC_BrowseDll:
		OnBrowse(TRUE);
		break;

	case IDC_BrowseCpp:
		OnBrowse(FALSE);
		break;

	case IDC_Options:
		OnOptions();
		break;

	case IDC_About:
		CAboutDlg::Show(m_hWnd);
		break;

	case IDCANCEL:
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);
		break;

	case IDC_DllFile:
		if (HIWORD(wParam) == EN_CHANGE)
		{
			// 自动生成输出文件名称
			if (GetDlgItemText(m_hWnd, IDC_DllFile, CAheadLib::m_tzDllFile, MAX_PATH))
			{
				TCHAR tzTemp[MAX_PATH];
				lstrcpy(tzTemp, CAheadLib::m_tzDllFile);
				PTSTR p = _StrRChr(tzTemp, '.');
				_ExIf(p == NULL, p = _StrEnd(tzTemp));
				lstrcpy(p, EXT_Cpp);
				SetDlgItemText(m_hWnd, IDC_CppFile, tzTemp);
				if (CAheadLib::m_bSystemPath)
				{
					*p = 0;
				}
				else
				{
					lstrcpy(p, TEXT("Org"));
				}
				p = _StrRChr(tzTemp, '\\');
				SetDlgItemText(m_hWnd, IDC_OriginDll, p ? p + 1 : tzTemp);
			}
			else
			{
				SetDlgItemText(m_hWnd, IDC_CppFile, NULL);
				SetDlgItemText(m_hWnd, IDC_OriginDll, NULL);
			}
		}
		break;

	case IDC_CppFile:
	case IDC_OriginDll:
		if (HIWORD(wParam) == EN_CHANGE)
		{
			// 获取原始 DLL 名称，设置按钮状态
			GetDlgItemText(m_hWnd, IDC_CppFile, CAheadLib::m_tzCppFile, MAX_PATH);
			GetDlgItemTextA(m_hWnd, IDC_OriginDll, CAheadLib::m_szOriginDll, MAX_PATH);
			p = _AStrRChr(CAheadLib::m_szOriginDll, '\\');
			lstrcpyA(CAheadLib::m_szOrigin, p ? p + 1 : CAheadLib::m_szOriginDll);
			p = _AStrRChr(CAheadLib::m_szOrigin, '.');
			_ExIf(p, *p = 0);
			EnableWindow(GetDlgItem(m_hWnd, IDOK), CAheadLib::m_tzCppFile[0] && CAheadLib::m_szOrigin[0]);
			if ((LOWORD(wParam) == IDC_OriginDll) && m_bShowOptions)
			{
				CAheadLib::Generate();
			}
		}
		break;

	case IDC_CallRedirect:
	case IDC_CallInTime:
	case IDC_LoadInEntry:
	case IDC_LoadIfNeed:
	case IDC_JumpToOrigin:
	case IDC_CallOrigin:
	case IDC_MultiThread:
	case IDC_SystemPath:
	case IDC_GenerateHook:
		CAheadLib::GetOptions();
		if (m_bShowOptions)
		{
			CAheadLib::Generate();
		}
		break;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 对话框系统命令消息
VOID WINAPI CMainDlg::OnSysCommand(WPARAM wParam)
{
	static BOOL s_bRestoreOptions = FALSE;

	if (wParam == SC_MAXIMIZE)
	{
		if (m_bShowOptions == FALSE)
		{
			m_bShowOptions = TRUE;
			s_bRestoreOptions = TRUE;
			CAheadLib::Generate();
		}
	}
	else if (wParam == SC_RESTORE)
	{
		if (s_bRestoreOptions)
		{
			m_bShowOptions = FALSE;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 大小改变
VOID WINAPI CMainDlg::OnSize(WPARAM wParam, LPARAM lParam)
{
	HWND hCtrl;
	RECT rtRect;

	if (wParam != SIZE_MINIMIZED)
	{
		hCtrl = GetDlgItem(m_hWnd, IDC_Preview);
		GetWindowRect(hCtrl, &rtRect);
		MapWindowPoints(NULL, m_hWnd, (PPOINT) &rtRect, 2);
		rtRect.right = LOWORD(lParam) - 10;
		rtRect.bottom = HIWORD(lParam) - 10;
		MoveWindow(hCtrl, rtRect.left, rtRect.top, _RectWidth(rtRect), _RectHeight(rtRect), TRUE);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 对话框销毁消息
VOID WINAPI CMainDlg::OnClose()
{
	//WINDOWPLACEMENT wpWindow;

	// 保存对话框位置信息
	//wpWindow.length = sizeof(WINDOWPLACEMENT);
	//GetWindowPlacement(m_hWnd, &wpWindow);
	//CIni::SetInt(INI_WindowLeft, wpWindow.rcNormalPosition.left);
	//CIni::SetInt(INI_WindowTop, wpWindow.rcNormalPosition.top);
	//CIni::SetInt(INI_WindowWidth, _RectWidth(wpWindow.rcNormalPosition));
	//CIni::SetInt(INI_WindowHeight, _RectHeight(wpWindow.rcNormalPosition));
	//CIni::SetInt(INI_WindowState, wpWindow.showCmd);

	// 保存选项
	CAheadLib::SaveOptions();
	CIni::SetInt(INI_ShowOptions, m_bShowOptions);

	// 关闭对话框
	EndDialog(m_hWnd, 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示隐藏选项
VOID WINAPI CMainDlg::OnOptions()
{
	if (IsZoomed(m_hWnd))
	{
		ShowWindow(m_hWnd, SW_RESTORE);
		m_bShowOptions = FALSE;
	}
	else
	{
		m_bShowOptions = !m_bShowOptions;
	}

	if (m_bShowOptions)
	{
		CAheadLib::Generate();
		CenterWindow(714, 486);
	}
	else
	{
		CenterWindow(334, 162);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 浏览文件
VOID WINAPI CMainDlg::OnBrowse(BOOL bDllFile)
{
	OPENFILENAME ofnName;
	TCHAR tzFileName[MAX_PATH];

	tzFileName[0] = 0;
	ZeroMemory(&ofnName, sizeof(OPENFILENAME));
	ofnName.lStructSize = sizeof(OPENFILENAME);
	ofnName.hwndOwner = m_hWnd;
	ofnName.lpstrFile = tzFileName;
	ofnName.nMaxFile = MAX_PATH;
	ofnName.lpstrDefExt = bDllFile ? EXT_Dll : EXT_Cpp;
	ofnName.lpstrFilter = bDllFile ? FILTER_Dll FILTER_All: FILTER_Cpp FILTER_All;
	if (bDllFile)
	{
		ofnName.Flags = OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		_ReturnIf(GetOpenFileName(&ofnName) == FALSE);
	}
	else
	{
		ofnName.Flags = OFN_ENABLESIZING | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
		_ReturnIf(GetSaveFileName(&ofnName) == FALSE);
	}
	SetDlgItemText(m_hWnd, bDllFile ? IDC_DllFile : IDC_CppFile, tzFileName);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
