#pragma once

#include <string>
#include <map>
#include <vector>

using WXContactModel = struct _WXContactModel {
	std::string wxid;
	std::string headerImgUrl;
	std::string nickname;
	std::string sex;
	std::string city;
	std::string account;
	std::string remarks;
};

using WXRoomModel = struct _WXRoomModel {
	std::string roomID;
	std::string headerImgUrl;
	std::string nickname;
	std::string remarks;
};

using WXPublicModel = struct _WXPublicModel {
	std::string publicID;
	std::string headerImgUrl;
	std::string nickname;
	std::string remarks;
};

using WXSettingModel = struct _WXSettingModel {
	bool openReceiveMessage;
	bool openAutoReplayMessage;
	bool openReceiveDownloadFileAtNight;
	bool openAutoReceiveTransfer;
	bool openAutoReceiveFriendRequest;
	bool openDisableRevokeMessage;
};