#pragma once

#include "Types.h"

class Account {
public:
	Account();
	~Account();

public:
	std::vector<WXContactModel> m_contactModel;
	std::vector<WXRoomModel> m_roomModel;
	std::vector<WXPublicModel> m_publicModel;
	WXSettingModel m_settingModel;

private:
	WXContactModel m_self;
};

