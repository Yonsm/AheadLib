


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#include "Main.h"
#include "AboutDlg.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 宏定义
#ifdef _CHS
#define FONT_NAME_AboutDlg		L"宋体"									// 字体名称
#else // _CHS
#define FONT_NAME_AboutDlg		L"MS Sans Serif"						// 字体名称
#endif // _CHS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AboutDlg 命名空间
namespace AboutDlg
{
#ifdef _CHS
	const WORD WIDTH_AboutDlg = 399;									// 对话框宽度
	const WORD HEIGHT_AboutDlg = 273;									// 对话框高度
	const WORD FONT_SIZE_AboutDlg = 9;									// 字体大小
#else // _CHS
	const WORD WIDTH_AboutDlg = 399;									// 对话框宽度
	const WORD HEIGHT_AboutDlg = 258;									// 对话框高度
	const WORD FONT_SIZE_AboutDlg = 8;									// 字体大小
#endif // _CHS

#if defined(_CHS) && defined(_UNICODE)
	const UINT WIDTH_Text = 12;											// 默认字体宽度
	const UINT HEIGHT_Text = 13;										// 默认字体高度
#else // defined(_CHS) && defined(_UNICODE)
	const UINT WIDTH_Text = 6;											// 默认字体宽度
	const UINT HEIGHT_Text = 13;										// 默认字体高度
#endif // defined(_CHS) && defined(_UNICODE)

	const UINT IDT_Close = 1534;										// 关闭时钟标识
	const COLORREF COLOR_Link = 0x00FF0000;								// 超链接颜色
	const COLORREF COLOR_HotLink = 0x000000FF;							// 鼠标热点超链接颜色

	// 对话框模板
	const struct DIALOGINFO
	{
		DLGTEMPLATE dtDialog;											// 对话框
		WORD wNoMenu;													// 没有对话框菜单
		WORD wNoClass;													// 没有对话框类名
		WORD wNoCaption;												// 没有对话框标题
		WORD wFontSize;													// 对话框字体大小
		WCHAR wszFontName[_NumberOf(FONT_NAME_AboutDlg)];				// 对话框字体名称
		__declspec(align(4)) WORD wEndOfDialog;							// 对话框结束标志
	}
	DI_Dialog =
	{
		{DS_SETFONT | DS_CENTER | WS_POPUP | WS_BORDER | WS_VISIBLE, 0, 0,
			0, 0, (WIDTH_AboutDlg * 2 / 3), (HEIGHT_AboutDlg * 2 / 3)},
			0, 0, 0, FONT_SIZE_AboutDlg, FONT_NAME_AboutDlg, 0
	};

	// 水平线组
	const struct LINEINFO
	{
		RECT rtRect;													// 位置
		COLORREF crColor;												// 颜色
	}
	LI_Lines[] =
	{
		{{0, 1, 88, 74}, 0x00FF9966},									// 蓝线组
		{{60, 116, WIDTH_AboutDlg, 132}, 0x00FF9966},					// 蓝线组
		{{60, 175, WIDTH_AboutDlg, 176}, 0x00000000},					// 一根白线
	};

	// 矩形
	const struct RECTINFO
	{
		RECT rtRect;													// 位置
		COLORREF crColor;												// 颜色
	}
	RI_Rects[] =
	{
		{{0, 75, WIDTH_AboutDlg, 111}, 0x00FF9966},						// 蓝色矩形
		{{0, 111, WIDTH_AboutDlg, 115}, 0x00CC3333},					// 深蓝色矩形
		{{60, 47, 116, 103}, 0x00CC3333},								// 图标外框深蓝色矩形
		{{64, 51, 112, 99}, 0x00FFFFFF},								// 图标外框白色矩形
		{{68, 55, 86, 73}, RGB(0xEE, 0xEE, 0xEE + VER_Major % 16)},		// 图标背景淡灰色矩形
		{{90, 55, 108, 73}, RGB(0xEE, 0xEE, 0xEE + VER_Minor % 16)},	// 图标背景淡灰色矩形
		{{68, 79, 86, 95}, RGB(0xEE, 0xEE, 0xEE + VER_Release % 16)},	// 图标背景淡灰色矩形
		{{90, 79, 108, 95}, RGB(0xEE, 0xEE, 0xEE + VER_Build % 16)},	// 图标背景淡灰色矩形
	};

	// 文本
	const struct TEXTINFO
	{
		INT x;															// X 坐标
		INT y;															// Y 坐标
		PCTSTR ptzText;													// 字符串
		COLORREF crColor;												// 颜色
	}
	TI_Texts[] =
	{
		{60, 162, CAboutDlg::m_tzStatus, 0x00000000},					// 状态信息
		{60, 140, STR_VersionStamp, 0x00BBBBBB},						// 版本信息
		{230, 140, STR_BuildStamp, 0x00BBBBBB},							// 编译信息
		{60, 240, STR_Description, 0x00000000},							// 描述信息
		{60, 255, STR_Copyright, 0x00000000},							// 版权信息
	};

	// 指定字体的字符串
	const struct FONTTEXTINFO
	{
		INT x;															// X 坐标
		INT y;															// Y 坐标
		PCTSTR ptzText;													// 字符串
		COLORREF crColor;												// 颜色
		LOGFONT lfFont;													// 字体
	}
	FTI_Texts[] =
	{
		{125, 40, STR_AppName, 0x00000000, {36, 0, 0, 0, 800, 1, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, 0, TEXT("Arial")}},
	};

	// 超链接
	const struct LINKINFO
	{
		RECT rtRect;													// 位置
		PCTSTR ptzTitle;												// 标题
		PCTSTR ptzTip;													// 提示字符串
		PCTSTR ptzUrl;													// 超链接目标 (HIWORD(ptzUrl) 为 0 表示命令消息)
	}
	LI_Links[] =
	{
		{
			{60, 185, 60 + _LengthOf(STR_CheckUpdate) * WIDTH_Text, 185 + HEIGHT_Text},
				STR_CheckUpdate, STR_CheckUpdateTip, (PCTSTR) IDC_CheckUpdate
		},
		{
			{60, 200, 60 + _LengthOf(STR_VisitWeb) * WIDTH_Text, 200 + HEIGHT_Text},
				STR_VisitWeb, STR_VisitWebTip, STR_VisitWebUrl
		},
			{
				{60, 215, 60 + _LengthOf(STR_WriteEmail) * WIDTH_Text, 215 + HEIGHT_Text},
					STR_WriteEmail, STR_WriteEmailTip, STR_WriteEmailUrl
			},
	};

	// 图标位置
	const RECT RT_Icon = RI_Rects[2].rtRect;

	// 状态信息位置
	const RECT RT_Status = {TI_Texts[0].x, TI_Texts[0].y, WIDTH_AboutDlg, TI_Texts[0].y + HEIGHT_Text};
};
using namespace AboutDlg;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAboutDlg 类静态成员变量
HWND CAboutDlg::m_hWnd = NULL;
BOOL CAboutDlg::m_bSplash = FALSE;
INT CAboutDlg::m_iLinkIndex = -1;
TCHAR CAboutDlg::m_tzStatus[64] = {0};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示关于对话框
VOID WINAPI CAboutDlg::Show(HWND hParent)
{
	if (m_hWnd == NULL)
	{
		DialogBoxIndirect(g_hInst, (LPDLGTEMPLATE) &DI_Dialog, hParent, AboutDlgProc);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 以 Splash 方式显示关于对话框
VOID WINAPI CAboutDlg::Splash(HWND hParent, UINT uTimer)
{
	if (m_hWnd == NULL)
	{
		// 创建无模式对话框
		CreateDialogIndirect(g_hInst, (LPDLGTEMPLATE) &DI_Dialog, hParent, AboutDlgProc);

		// 如果指定了自动关闭
		if (uTimer)
		{
			SetTimer(m_hWnd, IDT_Close, uTimer, NULL);
		}

		// 设置当前窗口以 Splash 方式显示的标记
		m_bSplash = TRUE;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 关闭窗口关于对话框
VOID WINAPI CAboutDlg::Close(UINT uTimer)
{
	// 如果是立即关闭
	if (uTimer)
	{
		SetTimer(m_hWnd, IDT_Close, uTimer, NULL);
	}
	else
	{
		// 删除定时器
		KillTimer(m_hWnd, IDT_Close);

		// 如果当前窗口以 Splash 方式显示
		if (m_bSplash)
		{
			DestroyWindow(m_hWnd);
			m_bSplash = FALSE;
		}
		else
		{
			EndDialog(m_hWnd, 0);
		}

		m_hWnd = NULL;
		m_tzStatus[0] = 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置状态信息
VOID WINAPI CAboutDlg::SetStatus(PCTSTR ptzText)
{
	HDC hDC;

	// 获取状态信息
	if (ptzText)
	{
		_StrToStr(m_tzStatus, ptzText);
	}
	else
	{
		m_tzStatus[0] = 0;
	}

	// 绘制状态信息
	hDC = GetDC(m_hWnd);
	SetTextColor(hDC, TI_Texts[0].crColor);
	FillRect(hDC, &RT_Status, (HBRUSH) GetStockObject(WHITE_BRUSH));
	SelectObject(hDC, (HFONT) SendMessage(m_hWnd, WM_GETFONT, 0, 0));
	TextOut(hDC, TI_Texts[0].x, TI_Texts[0].y, TI_Texts[0].ptzText, lstrlen(TI_Texts[0].ptzText));
	ReleaseDC(m_hWnd, hDC);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 关于对话框回调函数
INT_PTR CALLBACK CAboutDlg::AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	INT i;
	HDC hDC;
	POINT ptPoint;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		// 初始化变量
		m_hWnd = hWnd;
		m_iLinkIndex = NULL;

		// 设置鼠标指针
		SetClassLong(m_hWnd, GCL_HCURSOR, 0);
		SetCursor(LoadCursor(NULL, IDC_ARROW));

		// 设置对话框风格
		if (GetParent(m_hWnd) == NULL)
		{
			SetWindowLong(m_hWnd, GWL_EXSTYLE, (GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW));
			SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}
		break;

	case WM_CTLCOLORDLG:
	case WM_CTLCOLORSTATIC:
		return (INT_PTR) GetStockObject(WHITE_BRUSH);

	case WM_PAINT:
		OnPaint();
		break;

	case WM_ACTIVATEAPP:
		// 激活程序
		GetCursorPos(&ptPoint);
		MapWindowPoints(NULL, m_hWnd, &ptPoint, 1);
		SendMessage(m_hWnd, WM_MOUSEMOVE, 0, MAKELONG(ptPoint.x, ptPoint.y));
		break;

	case WM_MOUSEMOVE:
		// 如果鼠标所在位置的超链接改变
		ptPoint.x = LOWORD(lParam);
		ptPoint.y = HIWORD(lParam);
		i = GetLinkIndex(ptPoint);
		if (i != m_iLinkIndex)
		{
			m_iLinkIndex = i;
			hDC = GetDC(m_hWnd);
			PaintLinks(hDC);
			ReleaseDC(m_hWnd, hDC);
		}
		break;

	case WM_LBUTTONDOWN:
		// 如果在图标框内，拖动对话框
		ptPoint.x = LOWORD(lParam);
		ptPoint.y = HIWORD(lParam);
		if (PtInRect(&RT_Icon, ptPoint))
		{
			ReleaseCapture();
			PostMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}
		break;

	case WM_ENTERSIZEMOVE:
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		break;

	case WM_EXITSIZEMOVE:
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		break;

	case WM_LBUTTONUP:
		// 如果鼠标在超链接内
		if (m_iLinkIndex != -1)
		{
			// 如果 HIWORD(ptzUrl) 为 0，表示命令，否则表示超链接
			if (HIWORD(LI_Links[m_iLinkIndex].ptzUrl))
			{
				ShellExecute(NULL, NULL, LI_Links[m_iLinkIndex].ptzUrl, NULL, NULL, SW_NORMAL);
			}
			else
			{
				PostMessage(m_hWnd, WM_COMMAND, (WPARAM) LI_Links[m_iLinkIndex].ptzUrl, 0);
			}
		}
		else
		{
			// 关闭对话框
			Close();
		}
		break;

	case WM_COMMAND:
		// 处理命令消息
		switch (LOWORD(wParam))
		{
		case IDC_CheckUpdate:
			// 检查更新
			MessageBox(hWnd, TEXT("嘿嘿，在线升级功能尚未实现……"), STR_AppName, MB_ICONINFORMATION);
			break;

		case IDOK:
		case IDCANCEL:
			// 关闭对话框
			Close();
			break;
		}
		break;

	case WM_TIMER:
	case WM_RBUTTONUP:
		// 关闭对话框
		Close();
		break;
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 绘制对话框
VOID WINAPI CAboutDlg::OnPaint()
{
	INT i;
	INT j;
	HDC hDC;
	HPEN hPen;
	HBRUSH hBrush;
	POINT ptPoint;
	PAINTSTRUCT psPaint;

	// 开始绘制
	hDC = BeginPaint(m_hWnd, &psPaint);

	// 绘制水平线组
	for (i = 0; i < _NumberOf(LI_Lines); i++)
	{
		hPen = (HPEN) SelectObject(hDC, CreatePen(PS_SOLID, 0, LI_Lines[i].crColor));
		for(j = LI_Lines[i].rtRect.top; j < LI_Lines[i].rtRect.bottom; j += 2)
		{
			MoveToEx(hDC, LI_Lines[i].rtRect.left, j, NULL);
			LineTo(hDC, LI_Lines[i].rtRect.right, j);
		}
		DeleteObject(SelectObject(hDC, hPen));
	}

	// 绘制矩形区域
	for (i = 0; i < _NumberOf(RI_Rects); i++)
	{
		hBrush = CreateSolidBrush(RI_Rects[i].crColor);
		FillRect(hDC, &RI_Rects[i].rtRect, hBrush);
		DeleteObject(hBrush);
	}

	// 绘制图标
	DrawIcon(hDC,
		RT_Icon.left + (_RectWidth(RT_Icon) - 32) / 2,
		RT_Icon.top + (_RectHeight(RT_Icon) - 32) / 2,
		LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_Main)));

	// 绘制超链接
	GetCursorPos(&ptPoint);
	MapWindowPoints(NULL, m_hWnd, &ptPoint, 1);
	m_iLinkIndex = GetLinkIndex(ptPoint);
	PaintLinks(hDC);

	// 使用对话框默认字体、透明背景绘制文本
	SetBkMode(hDC, TRANSPARENT);
	SelectObject(hDC, (HFONT) SendMessage(m_hWnd, WM_GETFONT, 0, 0));
	for (i = 0; i < _NumberOf(TI_Texts); i++)
	{
		SetTextColor(hDC, TI_Texts[i].crColor);
		TextOut(hDC, TI_Texts[i].x, TI_Texts[i].y, TI_Texts[i].ptzText, lstrlen(TI_Texts[i].ptzText));
	}

	// 绘制指定字体的文本
	for (i = 0; i < _NumberOf(FTI_Texts); i++)
	{
		HFONT hFont = (HFONT) SelectObject(hDC, CreateFontIndirect(&FTI_Texts[i].lfFont));
		SetTextColor(hDC, FTI_Texts[i].crColor);
		TextOut(hDC, FTI_Texts[i].x, FTI_Texts[i].y, FTI_Texts[i].ptzText, lstrlen(FTI_Texts[i].ptzText));
		DeleteObject(SelectObject(hDC, hFont));
	}

	// 结束绘制
	EndPaint(m_hWnd, &psPaint);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 获取指定点的超链接
INT WINAPI CAboutDlg::GetLinkIndex(POINT ptPoint)
{
	for (INT i = 0; i < _NumberOf(LI_Links); i++)
	{
		if (PtInRect(&LI_Links[i].rtRect, ptPoint))
		{
			return i;
		}
	}
	return -1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 绘制超链接
VOID WINAPI CAboutDlg::PaintLinks(HDC hDC)
{
	HFONT hFont;
	LOGFONT lfFont;

	GetObject((HFONT) SendMessage(m_hWnd, WM_GETFONT, 0, 0), sizeof(LOGFONT), &lfFont);
	for (INT i = 0; i < _NumberOf(LI_Links); i++)
	{
		lfFont.lfUnderline = (i == m_iLinkIndex);
		hFont = (HFONT) SelectObject(hDC, CreateFontIndirect(&lfFont));
		SetTextColor(hDC, lfFont.lfUnderline ? COLOR_HotLink : COLOR_Link);
		TextOut(hDC, LI_Links[i].rtRect.left, LI_Links[i].rtRect.top,
			LI_Links[i].ptzTitle, lstrlen(LI_Links[i].ptzTitle));
		DeleteObject(SelectObject(hDC, hFont));
	}
	SetCursor(LoadCursor(NULL, ((m_iLinkIndex != -1) && _WinVerAboveEqual(4, 1)) ? IDC_HAND : IDC_ARROW));
	SetStatus((m_iLinkIndex == -1) ? NULL : LI_Links[m_iLinkIndex].ptzTip);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
