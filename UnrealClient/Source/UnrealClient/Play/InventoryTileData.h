// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInfo.h"
#include "UObject/NoExportTypes.h"
#include "InventoryTileData.generated.h"

/**
 * 
 */

UCLASS()
class UNREALCLIENT_API UInventoryTileData : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int	m_Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString	m_NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTexture2D* m_IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EItemTier	m_Tier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EItemType	m_Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EItemPart	m_Part;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<FItemOption>	m_OptionArray;
public:
	void SetIconTexture(UTexture2D* IconTex)
	{
		m_IconTexture = IconTex;
	}

	void SetName(const FString& NameText)
	{
		m_NameText = NameText;
	}

	UTexture2D* GetIconTexture()
	{
		return m_IconTexture;
	}

	FString GetName()
	{
		return m_NameText;
	}

	TArray<FItemOption> GetOption()
	{
		return m_OptionArray;
	}

	void SetOption(TArray<FItemOption> OptArray)
	{
		m_OptionArray = OptArray;
	}

	EItemPart GetPart()
	{
		return m_Part;
	}

	void SetPart(int Part)
	{
		m_Part = static_cast<EItemPart>(Part);
	}

	EItemTier GetTier()
	{
		return m_Tier;
	}

	void SetTier(int Tier)
	{
		m_Tier = static_cast<EItemTier>(Tier);
	}

	EItemType GetType()
	{
		return m_Type;
	}

	void SetType(int Type)
	{
		m_Type = static_cast<EItemType>(Type);;
	}

	int GetIndex()
	{
		return m_Index;
	}
	void SetIndex(int Index)
	{
		m_Index = Index;
	}
};