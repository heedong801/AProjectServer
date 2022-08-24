// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TileView.h"
#include "Components/Button.h"
#include "ItemInfo.h"
#include "InventoryTile.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UInventoryTile : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTileView* m_EquipTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTileView* m_CurrentEquipTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTileView* m_ConsumTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_EquipButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_ConsumableButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_CurrentEquipButton;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UItemDescWidget* m_ItemDescWidget;*/
	bool	m_MouseHovered;
	int32	m_ItemCount;


public:
	void LoadData(TArray<UObject*> EquipItemList, TArray<UObject*> ConsumeItemList, TArray<UObject*> QuestItemList);

	TArray<UObject*> GetEquipItemList() { return m_EquipTile->GetListItems(); }
	TArray<UObject*> GetCurrentEquipItemList() { return m_CurrentEquipTile->GetListItems(); }
	TArray<UObject*> GetConsumItemList() { return m_ConsumTile->GetListItems();}

	UTileView* GetEquipTile() { return m_EquipTile; }

	UFUNCTION()
		void ItemScroll(UObject* Data, UUserWidget* Widget);

	UFUNCTION()
		void ItemHovered(UObject* Data, bool Hovered);

	UFUNCTION()
	void CurrentEquipClick();

	UFUNCTION()
		void ConsumClick();

	UFUNCTION()
		void EquipClick();


	UFUNCTION()
		void ConsumItemClick(UObject* Data);

	UFUNCTION()
		void EquipItemClick(UObject* Data);
	UFUNCTION()
		void CurrentEquipItemClick(UObject* Data);

public:
	void AddItem(FPlayerItemData ItemInfo, UTexture2D* IconTex);
	void AddCurrentEquipItem(UObject* Data, UTexture2D* IconTex);

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTine);
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

};
