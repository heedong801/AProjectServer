#include "PreCompile.h"
#include "ThreadHandlerLoginMessage.h"
#include "ContentsSystemEnum.h"
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include <GameServerNet\DBConnecter.h>
#include "UserTable.h"
#include "CharacterTable.h"
#include "ItemTable.h"
#include <GameServerCore\DBQueue.h>
#include <functional>
#include "ContentsItemData.h"
#include <GameServerCore\NetQueue.h>
#include <GameServerCore\GameServerSectionManager.h>


// DB에 접속하는일
// 검증하는일
// 마지막으로 결과 패킷을 보내는 일까지
// 전부다 이안에서 벌어져야 하고
// 절대로 외부로 새어나가서는 안됩니다.

// 모든 이렇게 하겠지라고 착각하면 큰일납니다.
// 외우는 것이 아니라 코드를 짠사람의 의도를 파악해라.
// 보통 경력자한테 원하는 겁니다.

// 레퍼런스 카운트는 항상 1인 상태야.
ThreadHandlerLoginMessage::ThreadHandlerLoginMessage()
{

}

ThreadHandlerLoginMessage::~ThreadHandlerLoginMessage()
{

}

void ThreadHandlerLoginMessage::Start()
{
	if (nullptr == Session_)
	{
		GameServerDebug::LogError("Login TCPSession Error");
	}

	LoginResult_.Code = EGameServerCode::LoginError;
	DBWork(&ThreadHandlerLoginMessage::DBCheck);
}

void ThreadHandlerLoginMessage::DBCheck()
{
	std::string Name = GameServerThread::GetThreadName();

	UserTable_SelectIDToUserInfo SelectQuery(Message_->ID);
	SelectQuery.DoQuery();

	if (nullptr == SelectQuery.RowData)
	{
		UserTable_InsertUserInfo Insert = UserTable_InsertUserInfo(Message_->ID, Message_->PW);
		if (true == Insert.DoQuery())
		{
			UserTable_SelectIDToUserInfo InsertPostSelectQuery(Message_->ID);
			if (true == InsertPostSelectQuery.DoQuery())
			{
				SelectQuery.RowData = InsertPostSelectQuery.RowData;

				UserTable_UpdateUserInfo UpdateQuery = UserTable_UpdateUserInfo(Message_->ID, 1);

				if (true == UpdateQuery.DoQuery())
				{
					LoginResult_.Code = EGameServerCode::OK;
					GameServerDebug::LogInfo("UserTable_UpdateUserInfo Success Send");
				}
			}
		}
	}
	else
	{
		if (SelectQuery.RowData->ConnectStatus == 0)
		{
			UserTable_UpdateUserInfo UpdateQuery = UserTable_UpdateUserInfo(Message_->ID, 1);

			if (true == UpdateQuery.DoQuery())
			{
				LoginResult_.Code = EGameServerCode::OK;
				GameServerDebug::LogInfo("UserTable_UpdateUserInfo Success Send");

			}
		}
		else
			LoginResult_.Code = EGameServerCode::AlreadyPlay;
	}
	RowData = SelectQuery.RowData;

	NetWork(&ThreadHandlerLoginMessage::ResultSend);
}

void ThreadHandlerLoginMessage::ResultSend()
{
	if (LoginResult_.Code == EGameServerCode::OK)
	{
		GameServerDebug::LogInfo("Login Result Success Send");
		UserData = std::make_shared<ContentsUserData>();
		UserData->Data = *RowData;
		Session_->SetLink(EDataIndex::USERDATA, UserData);
		UserIndex_ = UserData->Data.Index;
	}

	GameServerSerializer Sr;
	LoginResult_.Serialize(Sr);
	Session_->Send(Sr.GetData());


	// 캐릭터 리스트 패킷을 받고 넘어가야죠.

	// 룸한테 넘길거죠?

	if (LoginResult_.Code == EGameServerCode::OK)
	{
		DBWork(&ThreadHandlerLoginMessage::DBCharacterListCheck);
	}
}


void ThreadHandlerLoginMessage::DBCharacterListCheck()
{
	UserData = Session_->GetLink<ContentsUserData>(EDataIndex::USERDATA);

	CharacterTable_SelectUserCharacters SelectQuery(UserIndex_);
	SelectQuery.DoQuery();
	
	Characters.Characters.resize(SelectQuery.RowDatas.size());

	for (size_t i = 0; i < SelectQuery.RowDatas.size(); i++)
	{
		Characters.Characters[i] = SelectQuery.RowDatas[i]->Info;
	}

	UserData->Characters = Characters.Characters;

	ItemTable_AllItemToItemInfo SelectItemQuery;
	SelectItemQuery.DoQuery();

	for (int i = 0; i < SelectItemQuery.RowDatas.size(); i++)
	{
		FPlayerItemData data;
		ItemRow row = *(SelectItemQuery.RowDatas[i]);

		data.ItemIndex = row.Index;
		data.ItemName = row.Name;
		data.ItemPart = row.ItemPart;
		data.ItemTier = row.ItemTier;
		data.ItemType = row.ItemType;
		
		ContentsItemData::AddItemData(data);
	}
	NetWork(&ThreadHandlerLoginMessage::CharctersSend);
}

void ThreadHandlerLoginMessage::CharctersSend()
{
	GameServerSerializer Sr;
	Characters.Serialize(Sr);
	Session_->Send(Sr.GetData());

	if (LoginResult_.Code == EGameServerCode::OK)
	{
		std::shared_ptr<ContentsUserData> Ptr = Session_->GetLink<ContentsUserData>(EDataIndex::USERDATA);
		Ptr->Data = *RowData;
	}

	
	GameServerDebug::LogInfo("Charcter List Send");
}