//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "LevelManager.h"
//#include "Kismet/GameplayStatics.h"
//#include "../UI/MainHUD.h"
//#include "../AProjectGameModeBase.h"
//#include "../DebugClass.h"
//#include "../AProjectGameInstance.h"
//#include "../Player/PlayerCharacter.h"
//#include "../UI/InventoryTile.h"
//void ULevelManager::OpenNextLevel()
//{
//	UGameplayStatics::OpenLevel(this, *m_NextMapName);
//}
//void ULevelManager::OpenTownLevel()
//{
//	UGameplayStatics::OpenLevel(this, *m_TownMapName);
//
//}
//
//void ULevelManager::OpenDelayLevel()
//{
//	/*UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
//	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
//
//	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
//	if (GameInst)
//	{
//		FPlayerInfo& SavePlayerInfo = GameInst->GetPlayerInfo();
//		FPlayerInfo& PlayerInfo = Player->GetPlayerInfo();
//	
//		if (&PlayerInfo && Player)
//		{
//			SavePlayerInfo.Name = PlayerInfo.Name;
//			SavePlayerInfo.Attack = PlayerInfo.Attack;
//			SavePlayerInfo.Armor = PlayerInfo.Armor;
//			SavePlayerInfo.HP = PlayerInfo.HP;
//			SavePlayerInfo.HPMax = PlayerInfo.HPMax;
//			SavePlayerInfo.MP = PlayerInfo.MP;
//			SavePlayerInfo.MPMax = PlayerInfo.MPMax;
//			SavePlayerInfo.Level = PlayerInfo.Level;
//			SavePlayerInfo.Exp = PlayerInfo.Exp;
//			SavePlayerInfo.Gold = PlayerInfo.Gold;
//			SavePlayerInfo.AttackDistance = PlayerInfo.AttackDistance;
//			SavePlayerInfo.AttackAngle = PlayerInfo.AttackAngle;
//			SavePlayerInfo.MoveSpeed = PlayerInfo.MoveSpeed;
//			SavePlayerInfo.SkillTree = PlayerInfo.SkillTree;
//			SavePlayerInfo.CriticalPercent = PlayerInfo.CriticalPercent;
//			SavePlayerInfo.CriticalDamage = PlayerInfo.CriticalDamage;
//			SavePlayerInfo.HPRecovery = PlayerInfo.HPRecovery;
//			SavePlayerInfo.MPRecovery = PlayerInfo.MPRecovery;
//		}
//
//	}
//	if (IsValid(GameMode))
//	{
//		UMainHUD* MainHUD = GameMode->GetMainHUD();
//		if (IsValid(MainHUD))
//		{
//			MainHUD->QuitAllWidgetAnim();
//			if (IsValid(MainHUD))
//			{
//				GameInst->SaveData();
//			}
//		}
//	}*/
//	GetWorld()->GetTimerManager().SetTimer(m_LevelOpenTimerHandle, this, &ULevelManager::OpenNextLevel, 3.1f, false, -1.f);
//}