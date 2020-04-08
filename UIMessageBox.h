#pragma once

#include "framework.h"

class UIMessageBox : public CWindowWnd, public INotifyUI {
public:
	~UIMessageBox();
public:
	UIMessageBox(CControlUI *pRootControl, HWND parentHWND);
	void Init(LPCTSTR xml, POINT point);
	LPCTSTR GetWindowClassName() const;
	void OnFinalMessage(HWND hWnd);
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	CControlUI *m_pRootControl;
	CPaintManagerUI m_pm;
	HWND m_hParent;
	LPCTSTR m_xml;
	POINT m_BasedPoint;
};

