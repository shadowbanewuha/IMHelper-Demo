#pragma once
#include "framework.h"

#include "Types.h"

class UIRoom : public CControlUI {
public:
	UIRoom();
	~UIRoom();

	void InitUI();
	void bindPaintManager(CPaintManagerUI *pm) { m_paint_manager = pm; InitUI(); }

	void HandleNotifyMessage(TNotifyUI& msg);

	void CreateRoom(std::vector<WXContactModel> members);
private:
	CPaintManagerUI *m_paint_manager;
	CDialogBuilder m_dlgBuilder;

	CListUI *m_pRoomList;
	CListUI *m_pRoomMemberList;
};