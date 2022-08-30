#include "ThreadHandlerSetCharacterStatMessage.h"
#include "../../DebugClass.h"
#include "../../Play/InventoryTile.h"
#include "../../Play/InventoryTileData.h"
#include "../../Play/EquipmentWidget.h"
#include "../../Play/CharacterHUD.h"
#include "../../Global/ClientBlueprintFunctionLibrary.h"
void ThreadHandlerSetCharacterStatMessage::Start()
{

	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(World_));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
		return;

	UEquipmentWidget* Equipment = Cast<UEquipmentWidget>(Inst->EquipmentUI);
	if (IsValid(Equipment) && Equipment != nullptr)
	{
		if(Message_->CharacterInfo.Att != -1)
			Inst->SelectCharacter.Att = Message_->CharacterInfo.Att;
		if (Message_->CharacterInfo.Armor != -1)
			Inst->SelectCharacter.Armor = Message_->CharacterInfo.Armor;
		if (Message_->CharacterInfo.HpMax != -1)
			Inst->SelectCharacter.HpMax = Message_->CharacterInfo.HpMax;
		if (Message_->CharacterInfo.MpMax != -1)
			Inst->SelectCharacter.MpMax = Message_->CharacterInfo.MpMax;
		if (Message_->CharacterInfo.Hp != -1 )
			Inst->SelectCharacter.Hp = Message_->CharacterInfo.Hp;
		if (Message_->CharacterInfo.Mp != -1)
			Inst->SelectCharacter.Mp = Message_->CharacterInfo.Mp;
		if (Message_->CharacterInfo.HpRecovery != -1)
			Inst->SelectCharacter.HpRecovery = Message_->CharacterInfo.HpRecovery;
		if (Message_->CharacterInfo.MpRecovery != -1)
			Inst->SelectCharacter.MpRecovery = Message_->CharacterInfo.MpRecovery;
		if (Message_->CharacterInfo.CriticalPercent != -1)
			Inst->SelectCharacter.CriticalPercent = Message_->CharacterInfo.CriticalPercent;
		if (Message_->CharacterInfo.CriticalDamage != -1)
			Inst->SelectCharacter.CriticalDamage = Message_->CharacterInfo.CriticalDamage;

		Equipment->SetStatText();
	}

	UCharacterHUD* CharacterHUD = Cast<UCharacterHUD>(Inst->CharacterHUD);
	if (IsValid(CharacterHUD) && CharacterHUD != nullptr)
	{

		if (Inst->SelectCharacter.Hp <= 0)
			Inst->SelectCharacter.Hp = 0;
		CharacterHUD->SetHPPercent(Inst->SelectCharacter.Hp / (float)Inst->SelectCharacter.HpMax);
	}
}

