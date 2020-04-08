#include "UIRoom.h"



UIRoom::UIRoom() {

}

UIRoom::~UIRoom() {

}

void UIRoom::InitUI() {
	m_pRoomList = static_cast<CListUI*>(m_paint_manager->FindControl(_T("room_list")));
	m_pRoomMemberList = static_cast<CListUI*>(m_paint_manager->FindControl(_T("room_member_list")));

}

void UIRoom::CreateRoom(std::vector<WXContactModel> members) {

}