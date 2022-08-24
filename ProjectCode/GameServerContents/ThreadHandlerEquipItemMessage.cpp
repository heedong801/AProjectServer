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
		}
		else
		{
			if (Message_->ChangeItemIndex != -1)
			{
				InventoryTable_DeleteItem DeleteQuery = InventoryTable_DeleteItem(Message_->ChangeItemIndex, Message_->CharacterIndex);

				if (false == DeleteQuery.DoQuery())
				{

				}
				else
				{

				}
			}
			if (Message_->CurrentItemIndex != -1)
			{
				InventoryTable_InsertItem InsertQuery = InventoryTable_InsertItem(Message_->CurrentItemIndex, Message_->CharacterIndex);

				if (false == InsertQuery.DoQuery())
				{

				}
				else
				{

				}
			}
		}
	}
		break;
	case 7:
	{
		EquipmentTable_UpdateArmorPart Query = EquipmentTable_UpdateArmorPart(Message_->CharacterIndex, Message_->CurrentItemIndex, Message_->ChangeItemIndex);
		if (false == Query.DoQuery())
		{
		}
		else
		{
			if (Message_->ChangeItemIndex != -1)
			{
				InventoryTable_DeleteItem DeleteQuery = InventoryTable_DeleteItem(Message_->ChangeItemIndex, Message_->CharacterIndex);

				if (false == DeleteQuery.DoQuery())
				{

				}
				else
				{

				}
			}
			if (Message_->CurrentItemIndex != -1)
			{
				InventoryTable_InsertItem InsertQuery = InventoryTable_InsertItem(Message_->CurrentItemIndex, Message_->CharacterIndex);

				if (false == InsertQuery.DoQuery())
				{

				}
				else
				{

				}
			}
		}
	}
	break;
	case 10:
	{
		EquipmentTable_UpdateMainHandPart Query = EquipmentTable_UpdateMainHandPart(Message_->CharacterIndex, Message_->CurrentItemIndex, Message_->ChangeItemIndex);
		if (false == Query.DoQuery())
		{
			
		}
		else
		{
			if (Message_->ChangeItemIndex != -1)
			{
				InventoryTable_DeleteItem InsertQuery = InventoryTable_DeleteItem(Message_->ChangeItemIndex, Message_->CharacterIndex);

				if (false == InsertQuery.DoQuery())
				{

				}
				else
				{

				}

			}
			if (Message_->CurrentItemIndex != -1)
			{
				InventoryTable_InsertItem DeleteQuery2 = InventoryTable_InsertItem(Message_->CurrentItemIndex, Message_->CharacterIndex);

				if (false == DeleteQuery2.DoQuery())
				{

				}
				else
				{

				}
			}
		}
	}
		break;
	case 11:
	{
		EquipmentTable_UpdateMainWristPart Query = EquipmentTable_UpdateMainWristPart(Message_->CharacterIndex, Message_->CurrentItemIndex, Message_->ChangeItemIndex);
		if (false == Query.DoQuery())
		{

		}
		else
		{
			if (Message_->ChangeItemIndex != -1)
			{
				InventoryTable_DeleteItem InsertQuery = InventoryTable_DeleteItem(Message_->ChangeItemIndex, Message_->CharacterIndex);

				if (false == InsertQuery.DoQuery())
				{

				}
				else
				{

				}

			}
			if (Message_->CurrentItemIndex != -1)
			{
				InventoryTable_InsertItem DeleteQuery2 = InventoryTable_InsertItem(Message_->CurrentItemIndex, Message_->CharacterIndex);

				if (false == DeleteQuery2.DoQuery())
				{

				}
				else
				{

				}
			}
		}
	}
	break;
	case 14:
	{
		EquipmentTable_UpdateOffHandPart Query = EquipmentTable_UpdateOffHandPart(Message_->CharacterIndex, Message_->CurrentItemIndex, Message_->ChangeItemIndex);
		if (false == Query.DoQuery())
		{

		}
		else
		{
			if (Message_->ChangeItemIndex != -1)
			{
				InventoryTable_DeleteItem InsertQuery = InventoryTable_DeleteItem(Message_->ChangeItemIndex, Message_->CharacterIndex);

				if (false == InsertQuery.DoQuery())
				{

				}
				else
				{

				}

			}
			if (Message_->CurrentItemIndex != -1)
			{
				InventoryTable_InsertItem DeleteQuery2 = InventoryTable_InsertItem(Message_->CurrentItemIndex, Message_->CharacterIndex);

				if (false == DeleteQuery2.DoQuery())
				{

				}
				else
				{

				}
			}
		}
	}
	break;
	case 17:
	{
		EquipmentTable_UpdateLeftHandPart Query = EquipmentTable_UpdateLeftHandPart(Message_->CharacterIndex, Message_->CurrentItemIndex, Message_->ChangeItemIndex);
		if (false == Query.DoQuery())
		{

		}
		else
		{
			if (Message_->ChangeItemIndex != -1)
			{
				InventoryTable_DeleteItem InsertQuery = InventoryTable_DeleteItem(Message_->ChangeItemIndex, Message_->CharacterIndex);

				if (false == InsertQuery.DoQuery())
				{

				}
				else
				{

				}

			}

			if (Message_->CurrentItemIndex != -1)
			{
				InventoryTable_InsertItem DeleteQuery2 = InventoryTable_InsertItem(Message_->CurrentItemIndex, Message_->CharacterIndex);

				if (false == DeleteQuery2.DoQuery())
				{

				}
				else
				{

				}
			}
		}
	}
	break;
	default:
		break;
	}


}

