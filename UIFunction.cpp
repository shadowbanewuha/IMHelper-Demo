#include "UIFunction.h"

static const LPCSTR kFunctionSubPageNameArray[] = {
	"add_mobile_friend_page",
	"add_room_member_page",
	"check_zombie_contact_page",
	"file_operate_page"
};

void UIFunction::AddContactToCheckZombieList(const std::vector<WXContactModel>& contacts) {
	m_pTabLayout->SelectItem(2);
}

void UIFunction::SwitchTabWithNotifyMessage(TNotifyUI& msg) {
	LPCTSTR name = msg.pSender->GetName().GetData();
	m_pTabLayout = static_cast<CTabLayoutUI*>(m_paint_manager->FindControl(_T("function_tab_controller")));
	for (int i = 0; i < 4; i++) {
		if (!strcmp(name, kFunctionSubPageNameArray[i])) {
			m_pTabLayout->SelectItem(i);
			break;
		}
	}
}