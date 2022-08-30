// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "SelectHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API USelectHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_WukongButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_NoneButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_StartButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_WukongText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_NoneText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBorder* m_WukongBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBorder* m_NoneBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBorder* m_MainBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UUserWidget* m_WukongDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCanvasPanel* m_SelectSubPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCanvasPanel* m_DescSubPanel;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = "true"), Transient)
		class UWidgetAnimation* m_FadeAnim;

	FTimerHandle m_PlayerAnimTimerHandle;
	FTimerHandle m_LevelOpenTimerHandle;
	TSubclassOf<APawn> m_Pawn;
	class ASelectPlayer* m_SelectPlayer;

	//FString FirstLevelName;
public:
	void SetPawn(TSubclassOf<APawn> Pawn) { m_Pawn = Pawn; }
	void OpenLevel();
	void OpenPlayLevel();

	UFUNCTION()
		void ChangeAnim();
	UFUNCTION()
		void WukongClick();
	UFUNCTION()
		void NoneClick();
	UFUNCTION()
		void StartClick();
	UFUNCTION()
		void BackClick();
protected:
	virtual void NativeConstruct();
};