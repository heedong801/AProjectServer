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

		
				
			

		
	}
	else
	{
		// 로그를 찍는다.
	}
}

