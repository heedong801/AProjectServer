#include "ThreadHandlerEquipItemResultMessage.h"
#include "../../DebugClass.h"
#include "../../Play/InventoryTile.h"
#include "../../Play/InventoryTileData.h"
#include "../../Play/EquipmentWidget.h"
#include "../../Global/ClientBlueprintFunctionLibrary.h"
void ThreadHandlerEquipItemResultMessage::Start()
{

	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(World_));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
		return;

	UEquipmentWidget* Equipment = Cast<UEquipmentWidget>(Inst->EquipmentUI);
	if (IsValid(Equipment) && Equipment != nullptr)
	{
		Inst->SelectCharacter.Att = Message_->CharacterInfo.Att;
		Inst->SelectCharacter.Armor = Message_->CharacterInfo.Armor;
		Inst->SelectCharacter.HpMax = Message_->CharacterInfo.HpMax;
		Inst->SelectCharacter.MpMax = Message_->CharacterInfo.MpMax;
		Inst->SelectCharacter.Hp = Message_->CharacterInfo.Hp;
		Inst->SelectCharacter.Mp = Message_->CharacterInfo.Mp;
		Inst->SelectCharacter.HpRecovery = Message_->CharacterInfo.HpRecovery;
		Inst->SelectCharacter.MpRecovery = Message_->CharacterInfo.MpRecovery;
		Inst->SelectCharacter.CriticalPercent = Message_->CharacterInfo.CriticalPercent;
		Inst->SelectCharacter.CriticalDamage = Message_->CharacterInfo.CriticalDamage;

		Equipment->SetStatText();
	}


}

