#include "ThreadHandlerGetEquipmentResultMessage.h"
#include "../../DebugClass.h"
#include "../../Play/InventoryTile.h"
#include "../../Play/InventoryTileData.h"
#include "../../Play/EquipmentWidget.h"
#include "../../Global/ClientBlueprintFunctionLibrary.h"

void ThreadHandlerGetEquipmentResultMessage::Start()
{

	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(World_));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
		return;


	UInventoryTile* Inventory = Cast<UInventoryTile>(Inst->InventoryUI);
	if (IsValid(Inventory) && Inventory != nullptr)
	{


		UEquipmentWidget* Equipment = Cast<UEquipmentWidget>(Inst->EquipmentUI);
		if (IsValid(Equipment) && Equipment != nullptr)
		{
			for (int i = 0; i < Message_->EquipItemData.size(); i++)
			{
				if (Message_->EquipItemData[i].ObjectIndex != 0 && Message_->EquipItemData[i].ItemIndex >= 0 && Message_->EquipItemData[i].ItemIndex <= 7)
				{
					const FUIItemTextureTableInfo* Info = Inst->FindItemTextureInfo(FString::FromInt(Message_->EquipItemData[i].ItemIndex));
					//LOG(TEXT("%d"), Message_->EquipItemData[i].ItemIndex);
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
						Data->SetIconTexture(Info->IconTexture);
						Equipment->SetPart(Data, static_cast<EItemPart>(Message_->EquipItemData[i].ItemPart), Info->IconTexture);

						Inventory->AddCurrentEquipItem(Data, Info->IconTexture);
					}
				}
			}

		}
	}

}

