#include "PreCompile.h"
#include "ThreadHandlerEquipItemMessage.h"
#include "EquipmentTable.h"
#include "InventoryTable.h"
ThreadHandlerEquipItemMessage::ThreadHandlerEquipItemMessage()
{
}

ThreadHandlerEquipItemMessage::~ThreadHandlerEquipItemMessage()
{
}

void ThreadHandlerEquipItemMessage::Start()
{
	if (nullptr == Session_)
	{
		GameServerDebug::LogError("Login TCPSession Error");
	}

	{
	}



	DBWork(&ThreadHandlerEquipItemMessage::DBCheck);
}


void ThreadHandlerEquipItemMessage::DBCheck()
{
	
	switch (Message_->ItemPart)
	{
	case 4:
	{
		EquipmentTable_UpdateNeckPart Query = EquipmentTable_UpdateNeckPart(Message_->CharacterIndex, Message_->CurrentItemIndex, Message_->ChangeItemIndex);
		if (false == Query.DoQuery())
		{
			InventoryTable_DeleteItem DeleteQuery = InventoryTable_DeleteItem(Message_->ChangeItemIndex);

			if (false == DeleteQuery.DoQuery())
			{

			}
			else
			{

			}

			InventoryTable_InsertItem InsertQuery = InventoryTable_InsertItem(Message_->CurrentItemIndex, Message_->CharacterIndex);

			if (false == InsertQuery.DoQuery())
			{

			}
			else
			{

			}

		}
		else
		{
		}
	}
		break;
	case 10:
		break;
	default:
		break;
	}


}

