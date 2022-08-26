// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillImageWidget.h"

void USkillImageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_CoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("CoolTimeBar")));
	m_SkillImg = Cast<UImage>(GetWidgetFromName(TEXT("SkillImg")));
	m_CoolTimeOn = true;
}

void USkillImageWidget::SetCoolTimePercent(float Percent, int32 CoolTime)
{
	m_CoolTimeBar->SetPercent(Percent);

	m_CoolTime = CoolTime;
	GetWorld()->GetTimerManager().SetTimer(m_CoolTimeHandle,
		this, &USkillImageWidget::SetCoolTime, 0.2f, true, -1.f);
	m_CoolTimeOn = false;
}
void USkillImageWidget::SetCoolTime()
{
	if (m_Percent >= m_CoolTime)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_CoolTimeHandle);
		m_Percent = 0.f;
		m_CoolTimeOn = true;
		return;
	}
	m_Percent += 0.2f;
	m_CoolTimeBar->SetPercent( 1.f - m_Percent / (float)m_CoolTime);
}
void USkillImageWidget::SetSkillImg(UTexture2D* Path)
{
	m_SkillImg->SetBrushFromTexture(Path);
}
