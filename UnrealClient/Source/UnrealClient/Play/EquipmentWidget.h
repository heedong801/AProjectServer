// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemInfo.h"
#include "EquipmentWidget.generated.h"

//enum class PART : uint8{ HEADBAND, HEAD, EYE, NECK, FACE, SHOULDER, ARMOR, CHEST, BODY, MAINHAND, MAINWRIST, BELT, OFFWRIST, OFFHAND,
//	RIGHTHAND,TROUSERS, LEFTHAND, RIGHTRING, FEET, LEFTRING};

UCLASS()
class UNREALCLIENT_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UImage*> m_EquipmentImgArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<class UInventoryTileData*> m_EquipmentItemArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_AttackText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_ArmorText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_MaxHPText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_MaxMPText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_HPRecoveryText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_MPRecoveryText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_CriPerText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_CriDmgText;

	FTimerDelegate m_ItemDurationDelegate;
	FTimerHandle m_ItemDurationTimerHandle;
protected:
	virtual void NativeConstruct();
	~UEquipmentWidget();
public:
	void SetPart(UInventoryTileData* Item, EItemPart Part, UTexture2D* Icon);
	void UnsetPart(class UInventoryTileData* Item);
	void SetStatText();
	UInventoryTileData* AlreadyPartSet(int PartIdx);
	int PartToIdx(const EItemPart& Part);


	TArray<class UInventoryTileData*> GetItemArray() {		return m_EquipmentItemArray;	}

	void LoadData(const TArray<class UInventoryTileData*>& ItemArray);

	UFUNCTION()
		void SetStat(UInventoryTileData* Item, bool bOnPlus);

};
