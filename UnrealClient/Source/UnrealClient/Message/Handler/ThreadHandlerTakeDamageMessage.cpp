#include "ThreadHandlerTakeDamageMessage.h"
#include "../../DebugClass.h"
#include "../../Play/InventoryTile.h"
#include "../../Play/InventoryTileData.h"
#include "../../Play/EquipmentWidget.h"
#include "../../Global/ClientBlueprintFunctionLibrary.h"
void ThreadHandlerTakeDamageMessage::Start()
{

	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(World_));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
		return;

	UEquipmentWidget* Equipment = Cast<UEquipmentWidget>(Inst->EquipmentUI);
	if (IsValid(Equipment) && Equipment != nullptr)
	{
		Inst->SelectCharacter.Hp = Message_->Hp;

		Equipment->SetStatText();
	}


}

