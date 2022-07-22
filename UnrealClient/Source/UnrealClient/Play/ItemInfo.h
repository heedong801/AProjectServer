// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemInfo.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Equipment,
	Consumable,
	Quest,
};

UENUM(BlueprintType)
enum class EItemOverlap : uint8
{
	None,
	Overlap
};

UENUM(BlueprintType)
enum class EItemTier : uint8
{
	Normal,
	Magic,
	Rare,
	Unique
};

UENUM(BlueprintType)
enum class EItemPart : uint8
{
	NONE, HEADBAND, HEAD, EYE, NECK, FACE, SHOULDER, ARMOR, CHEST, BODY, MAINHAND, MAINWRIST, BELT, OFFWRIST, OFFHAND,
	HAND, TROUSERS, RING, FEET
};

UENUM(BlueprintType)
enum class EItemOption : uint8
{
	Attack,
	Armor,
	HPMax,
	MPMax,
	HP,
	MP,
	HPRecovery,
	MPRecovery,
	CriticalPercent,
	CriticalDamage
};

USTRUCT(BlueprintType)
struct FItemOption
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EItemOption	OptionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float	Option;
};

USTRUCT(BlueprintType)
struct FUIItemTableInfo :
	public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString	Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EItemOverlap	Overlap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EItemType	ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EItemTier	ItemTier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EItemPart	ItemPart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString	Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<FItemOption>	OptionArray;

};