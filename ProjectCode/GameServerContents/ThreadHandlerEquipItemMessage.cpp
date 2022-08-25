#include "PreCompile.h"
#include "ThreadHandlerEquipItemMessage.h"
#include "EquipmentTable.h"
#include "InventoryTable.h"
#include "ContentsUserData.h"
#include "ContentsSystemEnum.h"
#include "OptionTable.h"
#include "CharacterTable.h"
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

	std::shared_ptr<ContentsUserData> Ptr = Session_->GetLink<ContentsUserData>(EDataIndex::USERDATA);

	OptionTable_SelectItemOption SelectItemQuery = OptionTable_SelectItemOption(Message_->CurrentItemIndex);
	if (false == SelectItemQuery.DoQuery())
	{

	}
	else
	{
		Ptr->SelectData.Att -= SelectItemQuery.RowData->Att;
		Ptr->SelectData.Armor -= SelectItemQuery.RowData->Armor;
		Ptr->SelectData.HpMax -= SelectItemQuery.RowData->HpMax;
		Ptr->SelectData.MpMax -= SelectItemQuery.RowData->MpMax;
		Ptr->SelectData.Hp -= SelectItemQuery.RowData->Hp;
		Ptr->SelectData.Mp -= SelectItemQuery.RowData->Mp;
		Ptr->SelectData.HpRecovery -= SelectItemQuery.RowData->HpRecovery;
		Ptr->SelectData.MpRecovery -= SelectItemQuery.RowData->MpRecovery;
		Ptr->SelectData.CriticalPercent -= SelectItemQuery.RowData->CriticalPercent;
		Ptr->SelectData.CriticalDamage -= SelectItemQuery.RowData->CriticalDamage;
	}

	OptionTable_SelectItemOption SelectCurrentItemQuery = OptionTable_SelectItemOption(Message_->ChangeItemIndex);
	if (false == SelectCurrentItemQuery.DoQuery())
	{

	}
	else
	{
		Ptr->SelectData.Att += SelectCurrentItemQuery.RowData->Att;
		Ptr->SelectData.Armor += SelectCurrentItemQuery.RowData->Armor;
		Ptr->SelectData.HpMax += SelectCurrentItemQuery.RowData->HpMax;
		Ptr->SelectData.MpMax += SelectCurrentItemQuery.RowData->MpMax;
		Ptr->SelectData.Hp += SelectCurrentItemQuery.RowData->Hp;
		Ptr->SelectData.Mp += SelectCurrentItemQuery.RowData->Mp;
		Ptr->SelectData.HpRecovery += SelectCurrentItemQuery.RowData->HpRecovery;
		Ptr->SelectData.MpRecovery += SelectCurrentItemQuery.RowData->MpRecovery;
		Ptr->SelectData.CriticalPercent += SelectCurrentItemQuery.RowData->CriticalPercent;
		Ptr->SelectData.CriticalDamage += SelectCurrentItemQuery.RowData->CriticalDamage;
	}

	CharacterTable_UpdateCharacter UpdateCharacterQuery = CharacterTable_UpdateCharacter(Ptr->SelectData.Index, Ptr->SelectData.Att, Ptr->SelectData.Armor, Ptr->SelectData.HpMax
		, Ptr->SelectData.MpMax, Ptr->SelectData.Hp, Ptr->SelectData.Mp, Ptr->SelectData.HpRecovery, Ptr->SelectData.MpRecovery, Ptr->SelectData.CriticalPercent, Ptr->SelectData.CriticalDamage);
	if (false == UpdateCharacterQuery.DoQuery())
	{

	}
	else
	{
		Result_.CharacterInfo.Att = Ptr->SelectData.Att;
		Result_.CharacterInfo.Armor = Ptr->SelectData.Armor;
		Result_.CharacterInfo.HpMax = Ptr->SelectData.HpMax;
		Result_.CharacterInfo.MpMax = Ptr->SelectData.MpMax;
		Result_.CharacterInfo.Hp = Ptr->SelectData.Hp;
		Result_.CharacterInfo.Mp = Ptr->SelectData.Mp;
		Result_.CharacterInfo.HpRecovery = Ptr->SelectData.HpRecovery;
		Result_.CharacterInfo.MpRecovery = Ptr->SelectData.MpRecovery;
		Result_.CharacterInfo.CriticalPercent = Ptr->SelectData.CriticalPercent;
		Result_.CharacterInfo.CriticalDamage = Ptr->SelectData.CriticalDamage;

		NetWork(&ThreadHandlerEquipItemMessage::ResultSend);

	}
}


void ThreadHandlerEquipItemMessage::ResultSend()
{
	GameServerSerializer Sr;
	Result_.Serialize(Sr);
	Session_->Send(Sr.GetData());
}
