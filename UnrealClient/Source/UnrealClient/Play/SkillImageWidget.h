// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "SkillImageWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API USkillImageWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProgressBar* m_CoolTimeBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UImage* m_SkillImg;

	FTimerHandle m_CoolTimeHandle;

	float m_Percent;
	int32 m_CoolTime;
	bool m_CoolTimeOn;
public:
	void SetCoolTimePercent(float Percent, int32 CoolTime);
	void SetCoolTime();
	void SetSkillImg(UTexture2D* Path);
	bool GetCoolTimeOn() { return m_CoolTimeOn; }
protected:
	virtual void NativeConstruct();
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
};