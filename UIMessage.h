#pragma once

#include "framework.h"

#include "Types.h"

class UIMessage : public CControlUI {
public:
	UIMessage();
	~UIMessage();

	void InitUI();
	void bindPaintManager(CPaintManagerUI *pm) { m_paint_manager = pm; InitUI(); }
	void HandleNotifyMessage(TNotifyUI& msg);

	void AddContactToGroup();
	void AddContactToGroup(const WXContactModel &contact, int groupIndex = 0);
private:
	CPaintManagerUI *m_paint_manager;
	CDialogBuilder m_dlgBuilder;

	CListUI *m_pSendGroupList;
	CListUI *m_pGroupMemberList;
	std::map<int, std::vector<WXContactModel>> m_mapGroupIndexToMemberList;
};

