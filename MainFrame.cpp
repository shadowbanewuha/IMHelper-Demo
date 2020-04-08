#include "MainFrame.h"

#include "UIFunction.h"
//#include "MenuWnd.h"
#include "UIMenu.h"
#include "UIMessage.h"
#include "UIMessageBox.h"

static LPCTSTR tabTitleArray[] = {
	"好友", "群聊", "公众号",
	"消息", "功能",
	"设置", "搜索好友"
};

MainFrame::MainFrame() {

}

MainFrame::~MainFrame() {

}

void MainFrame::Init() {
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("close_btn")));
	m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("max_btn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restore_btn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("min_btn")));
	m_pSearch = static_cast<CButtonUI*>(m_pm.FindControl(_T("search_contact_btn")));
	m_pAccountList = static_cast<CListUI*>(m_pm.FindControl(_T("account_list")));

	m_pMainTab = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("main_tab_controller")));
	m_pTitelLabel = static_cast<CLabelUI*>(m_pm.FindControl(_T("tab_title_label")));

	m_pFunctionController = static_cast<UIFunction*>(m_pm.FindControl(_T("function_frame")));
	m_pFunctionController->bindPaintManager(&m_pm);

	m_pMessageController = static_cast<UIMessage*>(m_pm.FindControl(_T("message_frame")));
	m_pMessageController->bindPaintManager(&m_pm);

	CScrollBarUI* pAccountScrollBarUI = m_pAccountList->GetVerticalScrollBar();
	pAccountScrollBarUI->SetAttribute(_T("width"), _T("0"));

	CListUI *pList = static_cast<CListUI*>(m_pm.FindControl(_T("friend_list")));
	for (int i = 0; i < 20; i++) {
		CDialogBuilder b;
		CListContainerElementUI *pListElement = static_cast<CListContainerElementUI*>(b.Create(_T("cell/cell_style7_item.xml"), (UINT)0, NULL, &m_pm));
		auto io = pListElement->FindSubControl("header_image_view");
		io->SetText("1");
		pList->Add(pListElement);
	}
}

LPCTSTR MainFrame::GetWindowClassName() const {
	return _T("UIMainWnd");
}

CDuiString MainFrame::GetSkinFile() {
	return _T("main_frame.xml");
}

CDuiString MainFrame::GetSkinFolder() {
	return  _T("skin\\WeChatRes\\");
}

void MainFrame::Notify(TNotifyUI& msg) {
	if (msg.sType != _T("itemselect") && m_pMessageBox) {
		m_pMessageBox->Close();
		m_pMessageBox = NULL;
	}
	if (msg.sType == _T("windowinit")) {
		OnPrepare(msg);
	}
	else if (msg.sType == _T("click")) {
		if (msg.pSender == m_pCloseBtn) {
			PostQuitMessage(0);
			return;
		}
		else if (msg.pSender == m_pMinBtn) {
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return;
		}
		else if (msg.pSender == m_pMaxBtn) {
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return;
		}
		else if (msg.pSender == m_pRestoreBtn) {
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return;
		}
		else if (msg.pSender == m_pSearch) {
			m_pMainTab->SelectItem(6);
			m_pTitelLabel->SetText(tabTitleArray[6]);
		}
	}
	else if (msg.sType == _T("itemclick")) {

	}
	else if (msg.sType == _T("menu")) {
		CMenuWnd* pMenu = new CMenuWnd(msg.pSender);
		CDuiPoint point = msg.ptMouse;
		ClientToScreen(m_hWnd, &point); 
		if (msg.pSender->GetName() == _T("friend_list")) {
			pMenu->Init(NULL, "menu/contact_list_menu.xml", _T("xml"), point);
			
		} else if (msg.pSender->GetName() == _T("send_group_list")) {
			pMenu->Init(NULL, "menu/send_group_list_menu.xml", _T("xml"), point);
		} else if (msg.pSender->GetName() == _T("send_group_member_list")) {
			pMenu->Init(NULL, "menu/send_group_member_list_menu.xml", _T("xml"), point);
		} else if (msg.pSender->GetName() == _T("room_list")) {
			pMenu->Init(NULL, "menu/room_list_menu.xml", _T("xml"), point);
		} else if (msg.pSender->GetName() == _T("room_member_list")) {
			pMenu->Init(NULL, "menu/room_member_list_menu.xml", _T("xml"), point);
		} else if (msg.pSender->GetName() == _T("add_mobile_contact_list")) {
			pMenu->Init(NULL, "menu/add_mobile_contact_list_menu.xml", _T("xml"), point);
		} else if (msg.pSender->GetName() == _T("add_room_contact_list")) {
			pMenu->Init(NULL, "menu/add_room_contact_list_menu.xml", _T("xml"), point);
		} else if (msg.pSender->GetName() == _T("check_zombie_contact_list")) {
			pMenu->Init(NULL, "menu/check_zombie_contact_list_menu.xml", _T("xml"), point);
		} else if (msg.pSender->GetName() == _T("search_friend_list")) {
			pMenu->Init(NULL, "menu/search_friend_list_menu.xml", _T("xml"), point);
		}
	}
	else if (msg.sType == _T("menu_item_click")) {
		handleMenuItemClickMessage(msg);
	} else if (msg.sType == _T("message_box_click")) {
		
	}
	else if (msg.sType == _T("itemselect")) {
		if (msg.pSender->GetName() == _T("friend_list")) {
			CListUI *pList = static_cast<CListUI*>(m_pm.FindControl(_T("account_list")));
			CListLabelElementUI *label = new CListLabelElementUI;
			label->SetBkImage("default_user_header.png");
			label->SetMinWidth(60);
			label->SetMinHeight(60);	
		} else if (msg.pSender->GetName() == _T("send_msg_type_combo")) {
			m_pMessageController->HandleNotifyMessage(msg);
		}
	}
	else if (msg.sType == _T("selectchanged")) {
		SwitchTabWithNotifyMessage(msg);
	}
	else if (msg.sType == _T("itemactivate")) {
		CDuiString parentName = msg.pSender->GetName();
		//if (parentName == _T("contact_list_main_menu")) {
			CListUI *pList = static_cast<CListUI*>(m_pm.FindControl(_T("account_list")));
			CListLabelElementUI *label = new CListLabelElementUI;
			label->SetBkImage("default_user_header.png");
			label->SetMinWidth(60);
			label->SetMinHeight(60);
			pList->Add(label);
		//}
	}
}

void MainFrame::SwitchTabWithNotifyMessage(TNotifyUI& msg) {

	CDuiString parentName = msg.pSender->GetParent()->GetName();
	if (parentName == _T("main_tab_controller_switch")) {
		CDuiString name = msg.pSender->GetName();
		if (name == _T("friend_page")) {
			m_pMainTab->SelectItem(0);
			m_pTitelLabel->SetText(tabTitleArray[0]);
		}
		else if (name == _T("room_page")) {
			m_pMainTab->SelectItem(1);
			m_pTitelLabel->SetText(tabTitleArray[1]);
		}
		else if (name == _T("public_page")) {
			m_pMainTab->SelectItem(2);
			m_pTitelLabel->SetText(tabTitleArray[2]);
		}
		else if (name == _T("message_page")) {
			m_pMainTab->SelectItem(3);
			m_pTitelLabel->SetText(tabTitleArray[3]);
		}
		else if (name == _T("function_page")) {
			m_pMainTab->SelectItem(4);
			m_pTitelLabel->SetText(tabTitleArray[4]);
		}
		else if (name == _T("setting_page")) {
			m_pMainTab->SelectItem(5);
			m_pTitelLabel->SetText(tabTitleArray[5]);
		}
	}
	else if (parentName == _T("function_tab_controller_switch")) {
		m_pFunctionController->SwitchTabWithNotifyMessage(msg);
	}
}

void MainFrame::handleMenuItemClickMessage(TNotifyUI& msg) {
	auto name = msg.pSender->GetName();
	if (name == _T("send_msg_menu_item")) {
		m_pMainTab->SelectItem(3);
		m_pTitelLabel->SetText(tabTitleArray[3]);
		m_pMessageController->AddContactToGroup();
	} else if (name == _T("create_room_menu_item")) {
		m_pMainTab->SelectItem(1);
		m_pTitelLabel->SetText(tabTitleArray[1]);
	} else if (name == _T("remark_contact_menu_item")) {
		UIMessageBox *box = new UIMessageBox(m_pRootControl, m_hWnd);
		CDuiPoint point = msg.ptMouse;
		ClientToScreen(m_hWnd, &point);
		box->Init(_T("tools/edit_msgbox.xml"), point);
		m_pMessageBox = box;
	} else if (name == _T("check_zombie_menu_item")) {
		m_pMainTab->SelectItem(4);
		m_pTitelLabel->SetText(tabTitleArray[4]);
	} else if (name == _T("delete_contact_menu_item")) {
		printf("d");
	} else if (name == _T("add_to_send_msg_group_menu_item")) {
		CMenuWnd* pMenu = new CMenuWnd(msg.pSender);
		CDuiPoint point = msg.ptMouse;
		ClientToScreen(m_hWnd, &point);
		pMenu->Init(NULL, "menu/contact_list_menu.xml", _T("xml"), point);
	} else if (name == _T("send_msg_group_menu_item")) {
		printf("d");
	} else if (name == _T("remark_room_menu_item")) {

	} else if (name == _T("delete_room_menu_item")) {

	} else if (name == _T("add_room_member_menu_item")) {

	} else if (name == _T("delete_mobile_contact_list_member_menu_item")) {
		printf("d");
	} else if (name == _T("delete_add_room_member_menu_item")) {

	} else if (name == _T("delete_check_zombie_contact_menu_item")) {

	} else if (name == _T("add_search_contact_menu_item")) {

	} else if (name == _T("delete_search_contact_menu_item")) {

	} else if (name == _T("rename_send_group_menu_item")) {

	} else if (name == _T("new_send_group_menu_item")) {

	} else if (name == _T("delete_send_group_menu_item")) {

	} else if (name == _T("add_contact_to_send_group_menu_item")) {

	} else if (name == _T("delete_contact_from_send_group_menu_item")) {

	}
}

void MainFrame::OnPrepare(TNotifyUI& msg) {

}

void MainFrame::OnExit(TNotifyUI& msg) {

}
void MainFrame::OnTimer(TNotifyUI& msg) {

}

LRESULT MainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	m_pm.Init(m_hWnd);
	m_pRootControl = m_dlgBuilder.Create(_T("main_frame.xml"), (UINT)0, NULL, &m_pm);
	ASSERT(m_pRootControl && "Failed to parse XML");
	m_pm.AttachDialog(m_pRootControl);
	m_pm.AddNotifier(this);
	Init();
	return 0;
}

LRESULT MainFrame::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT MainFrame::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return 0;
}

LRESULT MainFrame::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return 0;
}

LRESULT MainFrame::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if (!::IsZoomed(*this)) {
		RECT rcSizeBox = m_pm.GetSizeBox();
		if (pt.y < rcClient.top + rcSizeBox.top) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}

	RECT rcCaption = m_pm.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT MainFrame::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;
	lpMMI->ptMaxSize.x = rcWork.right;
	lpMMI->ptMaxSize.y = rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT MainFrame::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		RECT rc = { rcWnd.left, rcWnd.top + szRoundCorner.cx, rcWnd.right, rcWnd.bottom };
		HRGN hRgn1 = ::CreateRectRgnIndirect(&rc);
		HRGN hRgn2 = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom - szRoundCorner.cx, szRoundCorner.cx, szRoundCorner.cy);
		::CombineRgn(hRgn1, hRgn1, hRgn2, RGN_OR);
		::SetWindowRgn(*this, hRgn1, TRUE);
		::DeleteObject(hRgn1);
		::DeleteObject(hRgn2);
	}

	bHandled = FALSE;
	return 0;
}

LRESULT MainFrame::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
	if (wParam == SC_CLOSE) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(*this) != bZoomed) {
		if (!bZoomed) {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("max_btn")));
			if (pControl) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restore_btn")));
			if (pControl) pControl->SetVisible(true);
		}
		else {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("max_btn")));
			if (pControl) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restore_btn")));
			if (pControl) pControl->SetVisible(false);
		}
	}
	return lRes;
}

LRESULT MainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_CREATE:        
		lRes = OnCreate(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCACTIVATE:   
		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCCALCSIZE:   
		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_NCPAINT:     
		lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_NCHITTEST:   
		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_GETMINMAXINFO:
		lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled);
		break;
	case WM_SIZE:      
		lRes = OnSize(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_SYSCOMMAND:  
		lRes = OnSysCommand(uMsg, wParam, lParam, bHandled);
		break;
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}