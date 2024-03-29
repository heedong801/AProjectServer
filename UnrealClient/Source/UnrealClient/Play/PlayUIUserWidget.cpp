// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayUIUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../Global/ClientGameInstance.h"
#include "../Global/ClientBlueprintFunctionLibrary.h"
#include "../Message/ClientToServer.h"
#include "../Message/ServerToClient.h"
#include "../Message/ServerAndClient.h"
#include "../UnrealClient.h"

void UPlayUIUserWidget::RankWindowOpen()
{
	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}

	RankRequestMessage Msg;
	std::string NickNameText;
	UClientBlueprintFunctionLibrary::FStringToUTF8(Inst->NickName, NickNameText);

	Msg.NickName = NickNameText;
	GameServerSerializer Sr;
	Msg.Serialize(Sr);
	if (false == Inst->Send(Sr.GetData()))
	{
		return;
	}

	UPlayUIUserWidget::RankWindowOnOff();
}

void UPlayUIUserWidget::RankWindowOnOff()
{
	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}


	switch (Inst->RankWindowMode)
	{
	case ESlateVisibility::Visible:
		Inst->RankWindowMode = ESlateVisibility::Hidden;
		break;
	case ESlateVisibility::Hidden:
		Inst->RankWindowMode = ESlateVisibility::Visible;
		break;
	case ESlateVisibility::Collapsed:
	case ESlateVisibility::HitTestInvisible:
	case ESlateVisibility::SelfHitTestInvisible:
		UE_LOG(ClientLog, Error, TEXT("ModeError"));
		return;
	default:
		break;
	}

	if( Inst->RankWindow != nullptr )
		Inst->RankWindow->SetVisibility(Inst->RankWindowMode);
}

void UPlayUIUserWidget::NativeConstruct()
{
	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}


	Inst->PlayUI = this;
	Inst->EquipmentUI = GetWidgetFromName(TEXT("UI_Equipment"));
	Inst->InventoryUI = GetWidgetFromName(TEXT("UI_Inventory"));
	Inst->RankWindow = GetWidgetFromName(TEXT("RankWindow"));
	Inst->CharacterHUD = GetWidgetFromName(TEXT("UI_CharacterHUD"));

	if (nullptr == Inst->RankWindow ||
		false == Inst->RankWindow->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("Message List View Is Nullptr"));
		return;
	}

	if (nullptr == Inst->EquipmentUI ||
		false == Inst->EquipmentUI->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("EquipmentUI Is Nullptr"));
		return;
	}

	if (nullptr == Inst->InventoryUI ||
		false == Inst->InventoryUI->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("InventoryUI List View Is Nullptr"));
		return;
	}

	if (nullptr == Inst->CharacterHUD ||
		false == Inst->CharacterHUD->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("CharacterHUD List View Is Nullptr"));
		return;
	}

	Super::NativeConstruct();


	Inst->RankWindow->SetVisibility(Inst->RankWindowMode);
}

