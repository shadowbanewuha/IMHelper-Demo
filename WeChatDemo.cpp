// WeChatDemo.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WeChatDemo.h"

#include <exdisp.h>
#include <comdef.h>

#include "MainFrame.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin\\WeChatRes\\"));

	MainFrame* pFrame = new MainFrame();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("QQ2011"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 800);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();
	CPaintManagerUI::Term();

	return 0;
}

