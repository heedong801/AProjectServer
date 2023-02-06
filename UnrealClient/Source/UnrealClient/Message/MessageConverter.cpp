#include "MessageConverter.h"
#include <memory>
#include "MessageIdEnum.h"
#include "ServerToClient.h"
#include "ServerAndClient.h"
#include "ClientToServer.h"

MessageConverter::MessageConverter(const std::vector<unsigned char>&_buffer)
	: buffer_(_buffer)
{
	GameServerSerializer Sr = GameServerSerializer(buffer_);

	MessageId Type;
	memcpy_s(&Type, sizeof(MessageId), &buffer_[0], sizeof(MessageId));
	switch (Type)
	{
	case MessageId::Login:
		Message_ = std::make_shared<LoginMessage>();
		break;
	case MessageId::CreateCharacter:
		Message_ = std::make_shared<CreateCharacterMessage>();
		break;
	case MessageId::SelectCharacter:
		Message_ = std::make_shared<SelectCharacterMessage>();
		break;
	case MessageId::ClientToReady:
		Message_ = std::make_shared<ClientToReadyMessage>();
		break;
	case MessageId::LevelMoveReply:
		Message_ = std::make_shared<LevelMoveReplyMessage>();
		break;
	case MessageId::RankRequest:
		Message_ = std::make_shared<RankRequestMessage>();
		break;
	case MessageId::GetInventory:
		Message_ = std::make_shared<GetInventoryMessage>();
		break;
	case MessageId::EquipItem:
		Message_ = std::make_shared<EquipItemMessage>();
		break;
	case MessageId::Logout:
		Message_ = std::make_shared<LogoutMessage>();
		break;
	case MessageId::LoginResult:
		Message_ = std::make_shared<LoginResultMessage>();
		break;
	case MessageId::CharacterCreateResult:
		Message_ = std::make_shared<CharacterCreateResultMessage>();
		break;
	case MessageId::CharacterSelectResult:
		Message_ = std::make_shared<CharacterSelectResultMessage>();
		break;
	case MessageId::LevelMove:
		Message_ = std::make_shared<LevelMoveMessage>();
		break;
	case MessageId::UDPReadyOK:
		Message_ = std::make_shared<UDPReadyOKMessage>();
		break;
	case MessageId::SectionInsertResult:
		Message_ = std::make_shared<SectionInsertResultMessage>();
		break;
	case MessageId::ServerDestroy:
		Message_ = std::make_shared<ServerDestroyMessage>();
		break;
	case MessageId::PlayerDestroy:
		Message_ = std::make_shared<PlayerDestroyMessage>();
		break;
	case MessageId::ObjectDestroy:
		Message_ = std::make_shared<ObjectDestroyMessage>();
		break;
	case MessageId::CharacterList:
		Message_ = std::make_shared<CharacterListMessage>();
		break;
	case MessageId::PlayersUpdate:
		Message_ = std::make_shared<PlayersUpdateMessage>();
		break;
	case MessageId::MonsterUpdate:
		Message_ = std::make_shared<MonsterUpdateMessage>();
		break;
	case MessageId::UserRankWindowData:
		Message_ = std::make_shared<UserRankWindowDataMessage>();
		break;
	case MessageId::GetItem:
		Message_ = std::make_shared<GetItemMessage>();
		break;
	case MessageId::GetInventoryResult:
		Message_ = std::make_shared<GetInventoryResultMessage>();
		break;
	case MessageId::GetEquipmentResult:
		Message_ = std::make_shared<GetEquipmentResultMessage>();
		break;
	case MessageId::SetCharacterStat:
		Message_ = std::make_shared<SetCharacterStatMessage>();
		break;
	case MessageId::Chat:
		Message_ = std::make_shared<ChatMessage>();
		break;
	case MessageId::PlayerUpdate:
		Message_ = std::make_shared<PlayerUpdateMessage>();
		break;
	default:
		return;
	}
	Message_->DeSerialize(Sr);
}