#include "PreCompile.h"
#include "ThreadHandlerGetInventoryMessage.h"
#include "InventoryTable.h"
#include "ContentsItemData.h"
#include "EquipmentTable.h"

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



	DBWork(&ThreadHandlerGetInventoryMessage::DBCheck);
}


void ThreadHandlerGetInventoryMessage::DBCheck()
{
	InventoryTable_SelectAllItem SelectQuery = InventoryTable_SelectAllItem(Message_->CharacterIndex);

	if (false == SelectQuery.DoQuery())
	{
		// ContentsGlobalValue::UnRegistPlayable(SelectQuery.RowData->Index);

		Result_.Code = EGameServerCode::FAIL;

		NetWork(&ThreadHandlerGetInventoryMessage::ResultSend);
		return;
	}

	Result_.Code = EGameServerCode::OK;
	Result_.ItemData.resize(SelectQuery.RowDatas.size());

	ContentsItemData itemData;
	for (size_t i = 0; i < SelectQuery.RowDatas.size(); i++)
	{
		FPlayerItemData item = itemData.GetItemAtIndex(SelectQuery.RowDatas[i]->ItemIdx_);
		Result_.ItemData[i] = item;
	}

	EquipmentTable_SelectAllPart SelectAllQuery = EquipmentTable_SelectAllPart(Message_->CharacterIndex);

	if (false == SelectAllQuery.DoQuery())
	{
		// ContentsGlobalValue::UnRegistPlayable(SelectQuery.RowData->Index);
		Result_.Code = EGameServerCode::FAIL;


	}
	Result_.Code = EGameServerCode::OK;

	Result_.EquipItemData.resize(20);

	ContentsItemData itemData2;
	for (size_t i = 0; i < 20; i++)
	{
		if (i == 0)
			continue;
		if (SelectAllQuery.Data[i] != -1)
		{
			FPlayerItemData item = itemData2.GetItemAtIndex(SelectAllQuery.Data[i]);
			Result_.EquipItemData[i] = item;
		}

	}
	NetWork(&ThreadHandlerGetInventoryMessage::ResultSend);
}

void ThreadHandlerGetInventoryMessage::ResultSend()
{
	if (Result_.Code == EGameServerCode::OK)
	{
		GameServerSerializer Sr;
		Result_.Serialize(Sr);
		Session_->Send(Sr.GetData());

	
	}

}
