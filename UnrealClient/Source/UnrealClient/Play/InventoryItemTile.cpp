// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemTile.h"
#include "InventoryTileData.h"
#include "../DebugClass.h"
void UInventoryItemTile::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_IconImage = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	m_MagicTierImage = Cast<UImage>(GetWidgetFromName(TEXT("MagicTier")));
	m_RareTierImage = Cast<UImage>(GetWidgetFromName(TEXT("RareTier")));
	m_UniqueTierImage = Cast<UImage>(GetWidgetFromName(TEXT("UniqueTier")));


}

void UInventoryItemTile::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryItemTile::SetData(UObject* Data)
{
	UInventoryTileData* InvenData = Cast<UInventoryTileData>(Data);

	LOG(TEXT("%s"), *InvenData->GetName());
	UTexture2D* IconTexture = InvenData->GetIconTexture();

	if (IconTexture)
	{
		m_IconImage->SetBrushFromTexture(IconTexture);

		switch (InvenData->GetTier())
		{
		case EItemTier::Magic:
			m_MagicTierImage->SetVisibility(ESlateVisibility::Collapsed);
			m_RareTierImage->SetVisibility(ESlateVisibility::Collapsed);
			m_UniqueTierImage->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case EItemTier::Normal:
			m_MagicTierImage->SetVisibility(ESlateVisibility::Visible);
			m_RareTierImage->SetVisibility(ESlateVisibility::Collapsed);
			m_UniqueTierImage->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case EItemTier::Rare:
			m_MagicTierImage->SetVisibility(ESlateVisibility::Collapsed);
			m_RareTierImage->SetVisibility(ESlateVisibility::Visible);
			m_UniqueTierImage->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case EItemTier::Unique:
			m_MagicTierImage->SetVisibility(ESlateVisibility::Collapsed);
			m_RareTierImage->SetVisibility(ESlateVisibility::Collapsed);
			m_UniqueTierImage->SetVisibility(ESlateVisibility::Visible);
			break;
		}
	}

}


