#pragma once

#include "framework.h"

class UIContactList : public CListUI {
public:
	UIContactList(CPaintManagerUI& paint_manager);
	~UIContactList();

	bool Add(CControlUI* pControl);
	bool AddAt(CControlUI* pControl, int iIndex);
	bool Remove(CControlUI* pControl, bool bDoNotDestroy = false);
	bool RemoveAt(int iIndex, bool bDoNotDestroy);
	void RemoveAll();

private:
	CPaintManagerUI& m_paint_manager;
	CDialogBuilder m_dlgBuilder;
};

