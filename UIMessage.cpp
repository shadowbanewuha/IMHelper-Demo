#include "UIMessage.h"
#include "UIMenu.h"

UIMessage::UIMessage() {
}


UIMessage::~UIMessage() {
}

void UIMessage::InitUI() {
	m_pSendGroupList = static_cast<CListUI*>(m_paint_manager->FindControl(_T("send_group_list")));
	m_pGroupMemberList = static_cast<CListUI*>(m_paint_manager->FindControl(_T("send_group_member_list")));

	WXContactModel d;
	std::vector<WXContactModel> model;
	model.push_back(d);

	//m_mapGroupIndexToMemberList.insert(std::map<int, std::vector<WXContactModel>>::value_type(0, model));

	//m_mapGroupIndexToMemberList[0] = model;

	CListLabelElementUI *item = new CListLabelElementUI;
	item->SetText("ÁÙÊ±·Ö×é");
	item->SetFixedHeight(44);
	item->SetContextMenuUsed(true);
	m_pSendGroupList->Add(item);
}

void UIMessage::AddContactToGroup() {
	CDialogBuilder b;
	CListContainerElementUI *pListElement = static_cast<CListContainerElementUI*>(b.Create(_T("cell/cell_style3_item.xml"), (UINT)0, NULL, m_paint_manager));
	auto io = pListElement->FindSubControl("label0");
	io->SetText("1");
	m_pGroupMemberList->Add(pListElement);
}

void UIMessage::AddContactToGroup(const WXContactModel &contact, int groupIndex) {
	auto it = m_mapGroupIndexToMemberList.find(groupIndex);
	if (it != m_mapGroupIndexToMemberList.end()) {
		//std::vector<WXContactModel *>& vecMember = it->second;
		//vecMember.push_back(&contact);
		//CDialogBuilder b;
		//CListContainerElementUI *pListElement = static_cast<CListContainerElementUI*>(b.Create(_T("cell/cell_style3_item.xml"), (UINT)0, NULL, m_paint_manager));
		//auto io = pListElement->FindSubControl("label0");
		//io->SetText("1");
		//m_pGroupMemberList->Add(pListElement);
	}
}

void UIMessage::HandleNotifyMessage(TNotifyUI& msg) {
	if (msg.sType == _T("menu")) {

	} else if (msg.sType == _T("itemselect")) {
		CDuiString name = msg.pSender->GetName();
		if (name == _T("send_msg_type_combo")) {
			CComboUI *combo = static_cast<CComboUI*>(m_paint_manager->FindControl(_T("send_msg_type_combo")));
			CControlUI *pTextControl = static_cast<CControlUI*>(m_paint_manager->FindControl(_T("send_normal_msg_container")));
			CControlUI *pFileControl = static_cast<CControlUI*>(m_paint_manager->FindControl(_T("send_file_msg_container")));
			CControlUI *pCardControl = static_cast<CControlUI*>(m_paint_manager->FindControl(_T("send_card_msg_container")));
			CControlUI *pLinkControl = static_cast<CControlUI*>(m_paint_manager->FindControl(_T("send_link_container")));
			switch (combo->GetCurSel()) {
			case 0:
			{
				pTextControl->SetVisible(true);
				pFileControl->SetVisible(false);
				pCardControl->SetVisible(false);
				pLinkControl->SetVisible(false);
				break;
			}
			case 1:
			case 2:
			case 3:
			case 4:
			{
				pTextControl->SetVisible(false);
				pFileControl->SetVisible(true);
				pCardControl->SetVisible(false);
				pLinkControl->SetVisible(false);
				break;
			}
			case 5:
			{
				pTextControl->SetVisible(false);
				pFileControl->SetVisible(false);
				pCardControl->SetVisible(true);
				pLinkControl->SetVisible(false);
				break;
			}
			case 6:
			{
				pTextControl->SetVisible(false);
				pFileControl->SetVisible(false);
				pCardControl->SetVisible(false);
				pLinkControl->SetVisible(true);
				break;
			}
			default:
				break;
			}
		}
	}
}