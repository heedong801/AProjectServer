// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"
#include "InventoryTileData.h"
#include "ClientPlayCharacter.h"
#include "../Message/ContentsStructure.h"

#include "../DebugClass.h"
void UEquipmentWidget::NativeConstruct()
{
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("headband"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("head"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("eye"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("neck"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("face"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("shoulder"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("armor"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("chest"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("body"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("mainhand"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("mainwrist"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("belt"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("offwrist"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("offhand")))); //13
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("righthand")))); 
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("trousers"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("lefthand"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("rightring"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("feet"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("leftring"))));

	m_AttackText = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackText")));
	m_ArmorText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ArmorText")));
	m_MaxHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxHPText")));
	m_MaxMPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxMPText")));
	m_HPRecoveryText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPRecoveryText")));
	m_MPRecoveryText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MPRecoveryText")));
	m_CriPerText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CriticalPerText")));
	m_CriDmgText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CriticalDmgText")));

	m_EquipmentItemArray.Init(nullptr, 20);

	SetStatText();
}

void UEquipmentWidget::SetPart(UInventoryTileData* Item, EItemPart Part, UTexture2D* Icon)
{
	int Idx = PartToIdx(Part);

	if (Idx != -1)
	{
		if (m_EquipmentImgArray[Idx]->GetVisibility() != ESlateVisibility::Visible)
		{
			m_EquipmentImgArray[Idx]->SetBrushFromTexture(Icon);
			m_EquipmentImgArray[Idx]->SetVisibility(ESlateVisibility::Visible);

			m_EquipmentItemArray[Idx] = Item;
		}
		else
		{
			UnsetPart(m_EquipmentItemArray[Idx]);
			m_EquipmentImgArray[Idx]->SetBrushFromTexture(Icon);
			m_EquipmentImgArray[Idx]->SetVisibility(ESlateVisibility::Visible);

			m_EquipmentItemArray[Idx] = Item;
		}
	}

	SetStat(Item, true);
}

void UEquipmentWidget::UnsetPart(UInventoryTileData* Item)
{
	for (int32 i = 0; i < m_EquipmentItemArray.Num(); ++i)
	{
		if (m_EquipmentItemArray[i] == Item)
		{
			m_EquipmentImgArray[i]->SetVisibility(ESlateVisibility::Collapsed);
			SetStat(Item, false);
			break;
		}
	}

	
}

int32 UEquipmentWidget::PartToIdx(const EItemPart& Part)
{
	int Idx = -1;

	switch (Part)
	{
	case EItemPart::HEADBAND:
	case EItemPart::HEAD:
	case EItemPart::EYE:
	case EItemPart::NECK:
	case EItemPart::FACE:
	case EItemPart::SHOULDER:
	case EItemPart::ARMOR:
	case EItemPart::CHEST:
	case EItemPart::BODY:
	case EItemPart::MAINHAND:
	case EItemPart::MAINWRIST:
	case EItemPart::BELT:
	case EItemPart::OFFWRIST:
	case EItemPart::OFFHAND:
		Idx = static_cast<int>(Part) - 1;
		break;
	case EItemPart::HAND:
	{
		if (m_EquipmentImgArray[14]->GetVisibility() == ESlateVisibility::Collapsed)
			Idx = 14;
		else
			Idx = 16;
	}
	break;
	case EItemPart::TROUSERS:
		Idx = 15;
		break;
	case EItemPart::RING:
	{
		if (m_EquipmentImgArray[17]->GetVisibility() == ESlateVisibility::Collapsed)
			Idx = 17;
		else
			Idx = 19;
	}
	break;
	case EItemPart::FEET:
		Idx = 18;
		break;
	}

	return Idx;
}

UInventoryTileData* UEquipmentWidget::AlreadyPartSet(int PartIdx)
{
	if (m_EquipmentImgArray[PartIdx]->GetVisibility() != ESlateVisibility::Visible)
		return nullptr;
	else
		return m_EquipmentItemArray[PartIdx];
}

void UEquipmentWidget::SetStatText()
{
	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}
	FCharacterInfo Data = Inst->SelectCharacter;
	m_AttackText->SetText(FText::FromString(FString::FromInt(Data.Att)));
	m_ArmorText->SetText(FText::FromString(FString::FromInt(Data.Armor)));
	m_MaxHPText->SetText(FText::FromString(FString::FromInt(Data.HpMax)));
	m_MaxMPText->SetText(FText::FromString(FString::FromInt(Data.MpMax)));
	m_HPRecoveryText->SetText(FText::FromString(FString::FromInt(Data.HpRecovery)));
	m_MPRecoveryText->SetText(FText::FromString(FString::FromInt(Data.MpRecovery)));
	m_CriPerText->SetText(FText::FromString(FString::FromInt(Data.CriticalPercent)));
	m_CriDmgText->SetText(FText::FromString(FString::FromInt(Data.CriticalDamage)));

}

void UEquipmentWidget::SetStat(UInventoryTileData* Item, bool bOnPlus)
{
	AClientPlayCharacter* Player = Cast<AClientPlayCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	/*if (Player)
	{
		FPlayerInfo Info = Player->GetPlayerInfo();
		int Size = Item->GetOption().Num();
		if (bOnPlus)
		{
			for (int32 j = 0; j < Size; ++j)
			{
				EItemOption OptionType = Item->GetOption()[j].OptionType;
				float OptionValue = Item->GetOption()[j].Option;
				switch (OptionType)
				{
				case EItemOption::Attack:
					Info.Attack += OptionValue;
					if (Item->GetType() == EItemType::Consumable)
					{
						m_ItemDurationDelegate.BindUFunction(this, FName("SetStat"), Item, false);
						GetWorld()->GetTimerManager().SetTimer(m_ItemDurationTimerHandle,
							m_ItemDurationDelegate, 0.1f, false, 3.f);
					}
					continue;
				case EItemOption::Armor:
					Info.Armor += OptionValue;
					continue;
				case EItemOption::HPMax:
					Info.HPMax += OptionValue;
					continue;
				case EItemOption::MPMax:
					Info.MPMax += OptionValue;
					continue;
				case EItemOption::HP:
					Info.HP += OptionValue;
					Player->SetHPPercent();
					continue;
				case EItemOption::MP:
					Info.MP += OptionValue;
					Player->SetMPPercent();
					continue;
				case EItemOption::HPRecovery:
					Info.HPRecovery += OptionValue;
					continue;
				case EItemOption::MPRecovery:
					Info.MPRecovery += OptionValue;
					continue;
				case EItemOption::CriticalPercent:
					Info.CriticalPercent += OptionValue;
					continue;
				case EItemOption::CriticalDamage:
					Info.CriticalDamage += OptionValue;
					continue;
				}
			}
		}
		else
		{
			for (int32 j = 0; j < Size; ++j)
			{
				EItemOption OptionType = Item->GetOption()[j].OptionType;
				float OptionValue = Item->GetOption()[j].Option;
				switch (OptionType)
				{
				case EItemOption::Attack:
					Info.Attack -= OptionValue;
					continue;
				case EItemOption::Armor:
					Info.Armor -= OptionValue;
					continue;
				case EItemOption::HPMax:
					Info.HPMax -= OptionValue;
					continue;
				case EItemOption::MPMax:
					Info.MPMax -= OptionValue;
					continue;
				case EItemOption::HP:
					continue;
				case EItemOption::MP:
					continue;
				case EItemOption::HPRecovery:
					Info.HPRecovery -= OptionValue;
					continue;
				case EItemOption::MPRecovery:
					Info.MPRecovery -= OptionValue;
					continue;
				case EItemOption::CriticalPercent:
					Info.CriticalPercent -= OptionValue;
					continue;
				case EItemOption::CriticalDamage:
					Info.CriticalDamage -= OptionValue;
					continue;
				}
			}
		}
		Player->SetPlayerInfo(Info);
	}
	SetStatText();*/
}

void UEquipmentWidget::LoadData(const TArray<class UInventoryTileData*>& ItemArray)
{
	if (ItemArray.Num() != 0 )
		m_EquipmentItemArray = ItemArray;

	for (int32 i = 0; i < m_EquipmentItemArray.Num(); ++i)
	{
		if (m_EquipmentItemArray[i] != nullptr)
		{
			m_EquipmentImgArray[i]->SetBrushFromTexture(m_EquipmentItemArray[i]->GetIconTexture());
			m_EquipmentImgArray[i]->SetVisibility(ESlateVisibility::Visible);
		}
	}
}