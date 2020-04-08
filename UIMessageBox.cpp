#include "UIMessageBox.h"

UIMessageBox::UIMessageBox(CControlUI *pRootControl, HWND hWnd) :
	m_pRootControl(pRootControl),
	m_hParent(hWnd) {

}

UIMessageBox::~UIMessageBox() {

}

void UIMessageBox::Init(LPCTSTR xml, POINT point) {
	m_xml = xml;
	m_BasedPoint = point;
	Create(m_hParent, NULL, WS_POPUP, WS_EX_TOOLWINDOW | WS_EX_TOPMOST, CDuiRect());
	// HACK: Don't deselect the parent's caption
	//while (::GetParent(hWndParent) != NULL) hWndParent = ::GetParent(hWndParent);
	::ShowWindow(m_hWnd, SW_SHOW);
#if defined(WIN32) && !defined(UNDER_CE)
	::SendMessage(m_hParent, WM_NCACTIVATE, TRUE, 0L);
#endif	
}

LPCTSTR UIMessageBox::GetWindowClassName() const {
	return _T("MessageBox");
}

void UIMessageBox::OnFinalMessage(HWND hWnd) {
	delete this;
}

void UIMessageBox::Notify(TNotifyUI& msg) {
	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("confirm_change_contact_nickname")) {
			printf("d");
		} else if (msg.pSender->GetName() == _T("cancel_change_contact_nickname")) {
			printf("d");
		}
		m_pRootControl->GetManager()->SendNotify(msg.pSender, _T("message_box_click"), msg.wParam, msg.lParam, true);
	}
}

LRESULT UIMessageBox::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_CREATE) {
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		RECT rcClient;
		::GetClientRect(*this, &rcClient);
		::SetWindowPos(*this, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, 
			rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);
		m_pm.Init(m_hWnd);

		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(m_xml, (UINT)0, NULL, &m_pm);
		m_pm.AttachDialog(pRoot);
		m_pm.AddNotifier(this);

		CControlUI *box = static_cast<CControlUI*>(m_pm.FindControl(_T("box")));
		RECT rc;
		GetWindowRect(m_hParent, &rc);
		LONG width = box->GetFixedWidth();
		LONG height = box->GetFixedHeight();
		LONG left = (rc.right - rc.left - width) / 2;
		LONG top = (rc.bottom - rc.top - height) / 2;
		MoveWindow(m_hWnd, left+rc.left, top+rc.top, width, height, false);
	}
	LRESULT lRes = 0;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}