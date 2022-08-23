#include "ThreadHandlerGetInventoryResultMessage.h"
#include "../../DebugClass.h"
#include "../../Play/InventoryTile.h"
#include "../../Play/InventoryTileData.h"
#include "../../Play/EquipmentWidget.h"
#include "../../Global/ClientBlueprintFunctionLibrary.h"
void ThreadHandlerGetInventoryResultMessage::Start()
{
	if (EGameServerCode::OK == Message_->Code)
	{
		UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(World_));

		if (nullptr == Inst || false == Inst->IsValidLowLevel())
			return;

	

		UInventoryTile* Inventory = Cast<UInventoryTile>(Inst->InventoryUI);
		if (IsValid(Inventory) && Inventory != nullptr)
		{
			for (int i = 0; i < Message_->ItemData.size(); i++)
			{
				const FUIItemTextureTableInfo* Info = Inst->FindItemTextureInfo(FString::FromInt(Message_->ItemData[i].ItemIndex));
				//Inst->m_EquipItemList.Add(ItemMessage->ItemData);
				if (Info != nullptr)
					Inventory->AddItem(Message_->ItemData[i], Info->IconTexture);
			}

		}

		UEquipmentWidget* Equipment = Cast<UEquipmentWidget>(Inst->EquipmentUI);
		if (IsValid(Equipment) && Equipment != nullptr)
		{
			for (int i = 0; i < Message_->EquipItemData.size(); i++)
			{
				const FUIItemTextureTableInfo* Info = Inst->FindItemTextureInfo(FString::FromInt(Message_->EquipItemData[i].ItemIndex));
			
				if (Info != nullptr)
				{	
					UInventoryTileData* Data = NewObject<UInventoryTileData>(Inventory,
						UInventoryTileData::StaticClass());

					FString ItemName;
					UClientBlueprintFunctionLibrary::UTF8ToFString(Message_->EquipItemData[i].ItemName, ItemName);
					Data->SetName(ItemName);
					//Data->SetIndex(m_InventoryTile->GetNumItems());
					Data->SetTier(Message_->EquipItemData[i].ItemTier);
					Data->SetType(Message_->EquipItemData[i].ItemType);
					Data->SetPart(Message_->EquipItemData[i].ItemPart);
					Data->SetIndex(Message_->EquipItemData[i].ItemIndex);

					Equipment->SetPart(Data, static_cast<EItemPart>(Message_->EquipItemData[i].ItemPart), Info->IconTexture);
				}
			}

		}
	}
	else
	{
		// 로그를 찍는다.
	}
}

