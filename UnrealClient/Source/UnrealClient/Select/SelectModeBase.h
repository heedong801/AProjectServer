// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectHUD.h"
#include "GameFramework/GameModeBase.h"
#include "SelectModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API ASelectModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<USelectHUD>	m_SelectHUDClass;

	USelectHUD* m_SelectHUD;

	TSubclassOf<APawn> m_Pawn;
public:
	ASelectModeBase();

public:

	USelectHUD* GetSelectHUD()
	{
		return m_SelectHUD;
	}

	void SpawnCharacter();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void BeginPlay();
};