#include "PreCompile.h"
#include "ThreadHandlerGetInventoryMessage.h"

ThreadHandlerGetInventoryMessage::ThreadHandlerGetInventoryMessage()
{
}

ThreadHandlerGetInventoryMessage::~ThreadHandlerGetInventoryMessage()
{
}

void ThreadHandlerGetInventoryMessage::Start()
{
	if (nullptr == Session_)
	{
		GameServerDebug::LogError("Login TCPSession Error");
	}

	{
	}



	//DBWork(&ThreadHandlerSelectCharacterMessage::DBCheck);
}


void ThreadHandlerGetInventoryMessage::DBCheck()
{
	//CharacterTable_SelectNickName SelectQuery = CharacterTable_SelectNickName(Message_->NickName);

	//if (false == SelectQuery.DoQuery())
	//{
	//	// ContentsGlobalValue::UnRegistPlayable(SelectQuery.RowData->Index);

	//	ResultMessage.Code = EGameServerCode::FAIL;
	//	NetWork(&ThreadHandlerSelectCharacterMessage::SelectResult);
	//	return;
	//}

	////if (false == ContentsGlobalValue::RegistPlayable(SelectQuery.RowData->Index))
	////{
	////	ResultMessage.Code = EGameServerCode::FAIL;
	////	NetWork(&ThreadHandlerSelectCharacterMessage::SelectResult);
	////	return;
	////}

	//ResultMessage.Code = EGameServerCode::OK;

	//NetWork(&ThreadHandlerSelectCharacterMessage::SelectResult);
}

void ThreadHandlerGetInventoryMessage::SelectResult()
{
	//std::shared_ptr<ContentsUserData> UserData = Session_->GetLink<ContentsUserData>(EDataIndex::USERDATA);

	//if (ResultMessage.Code == EGameServerCode::OK)
	//{
	//	for (size_t i = 0; i < UserData->Characters.size(); i++)
	//	{
	//		if (UserData->Characters[i].NickName == Message_->NickName)
	//		{
	//			// 룸으로 보낸다는 생각하지 않겠습니다.
	//			GameServerSerializer Sr;
	//			ResultMessage.NickName = Message_->NickName;
	//			ResultMessage.Serialize(Sr);
	//			Session_->Send(Sr.GetData());
	//			GameServerDebug::LogInfo("Select Result OK Send");
	//			UserData->SelectData = UserData->Characters[i];

	//			NetWork(&ThreadHandlerSelectCharacterMessage::SectionInsert);

	//			return;
	//		}
	//	}
	//}

	//ResultMessage.Code = EGameServerCode::FAIL;
	//GameServerSerializer Sr;
	//ResultMessage.Serialize(Sr);
	//Session_->Send(Sr.GetData());

	//GameServerDebug::LogInfo("Select Result FAIL Send");
	// 실패했는데 캐릭터를 만들필요가 없으니까 그냥 여기서 끝낸다.
	// NetWork(&ThreadHandlerSelectCharacterMessage::SectionInsert);
}

