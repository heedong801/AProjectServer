#include "PreCompile.h"
#include "ThreadHandlerCreateCharacterMessage.h"
#include "ThreadHandlerLoginMessage.h"
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include <GameServerNet\DBConnecter.h>
#include "UserTable.h"
#include <GameServerCore\DBQueue.h>
#include <functional>
#include <GameServerCore\NetQueue.h>
#include <GameServerCore\GameServerSectionManager.h>
#include "ContentsSystemEnum.h"
#include "ContentsUserData.h"
#include "CharacterTable.h"
#include "EquipmentTable.h"
ThreadHandlerCreateCharacterMessage::ThreadHandlerCreateCharacterMessage() 
{
}

ThreadHandlerCreateCharacterMessage::~ThreadHandlerCreateCharacterMessage() 
{
}

void ThreadHandlerCreateCharacterMessage::Start() 
{
	if (nullptr == Session_)
	{
		GameServerDebug::LogError("Login Session Error");
	}

	Result_.Code = EGameServerCode::LoginError;
	DBWork(&ThreadHandlerCreateCharacterMessage::DBCheck);
}


void ThreadHandlerCreateCharacterMessage::DBCheck() 
{
	std::shared_ptr<ContentsUserData> Ptr = Session_->GetLink<ContentsUserData>(EDataIndex::USERDATA);

	CharacterTable_SelectNickName SelectQuery = CharacterTable_SelectNickName(Message_->NickName);
	if (false == SelectQuery.DoQuery())
	{
		CharacterTable_CreateCharacter InsertQuery = CharacterTable_CreateCharacter(Message_->NickName, Ptr->Data.Index);
		if (false == InsertQuery.DoQuery())
		{
			Result_.Code = EGameServerCode::FAIL;
		}
		else 
		{
			CharacterTable_SelectNickName ResultSelectQuery = CharacterTable_SelectNickName(Message_->NickName);

			if (false == ResultSelectQuery.DoQuery())
			{
				Result_.Code = EGameServerCode::FAIL;
			}
			else
			{
				Result_.Code = EGameServerCode::OK;
				Result_.ResultCharacter = ResultSelectQuery.RowData->Info;

				EquipmentTable_InsertCharacter InsertEquipQuery = EquipmentTable_InsertCharacter(Result_.ResultCharacter.Index);

				if (false == InsertEquipQuery.DoQuery())
					Result_.Code = EGameServerCode::FAIL;
				else
					Result_.Code = EGameServerCode::OK;
			}
		}

		Ptr->Characters.push_back(Result_.ResultCharacter);
		GameServerDebug::LogInfo("Character Create Success Send");

	}
	else 
	{
		Result_.Code = EGameServerCode::DuplicateID;
		GameServerDebug::LogInfo("Character Create Fail Send");
	}

	NetWork(&ThreadHandlerCreateCharacterMessage::Result);
}

void ThreadHandlerCreateCharacterMessage::Result() 
{
	//std::shared_ptr<ContentsUserData> Ptr = std::make_shared<ContentsUserData>();
	//Ptr->Data = *RowData;
	//TCPSession_->SetLink(EDataIndex::USERDATA, Ptr);

	GameServerSerializer Sr;
	Result_.Serialize(Sr);
	Session_->Send(Sr.GetData());



}