// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHUD.h"
#include "../DebugClass.h"
//#include "SkillImageWidget.h"
void UCharacterHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_LevelText = Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelText")));
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	m_MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));	
	m_EXPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("EXPBar")));
	//m_SkillArray.Add(Cast<USkillImageWidget>(GetWidgetFromName(TEXT("UI_Skill1"))));
	//m_SkillArray.Add(Cast<USkillImageWidget>(GetWidgetFromName(TEXT("UI_Skill2"))));

	//APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	/*if (Player)
	{
		SetLevelText(Player->GetPlayerInfo().Level);
		SetEXPPercent(Player->GetPlayerInfo().Exp);
	}*/
}

void UCharacterHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


