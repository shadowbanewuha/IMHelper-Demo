#pragma once

#include "framework.h"
#include "Types.h"

class UIFunction : public CControlUI {
public:
	UIFunction() { }
	~UIFunction() { }

	void bindPaintManager(CPaintManagerUI *pm) { m_paint_manager = pm; }
	void SwitchTabWithNotifyMessage(TNotifyUI& msg);

	void AddContactToCheckZombieList(const std::vector<WXContactModel>& contacts);
private:
	CPaintManagerUI *m_paint_manager;
	CDialogBuilder m_dlgBuilder;

	CTabLayoutUI *m_pTabLayout;
};

