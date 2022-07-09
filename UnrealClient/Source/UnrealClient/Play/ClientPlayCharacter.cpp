#include "ClientPlayCharacter.h"
#include "../UnrealClient.h"
#include "ObjectMessageComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Global/ClientGameInstance.h"
#include "../Play/PlayGameMode.h"
#include "../Play/ClientMonster.h"
#include "../Message/ClientToServer.h"
#include "../Message/ServerToClient.h"
#include "../Message/ServerAndClient.h"
#include "Animation/AnimMontage.h"
#include "ClientAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "ClientOtherCharacter.h"
#include "GameFramework/PlayerInput.h"
#include "DrawDebugHelpers.h"
#include"../DebugClass.h"

// Sets default values
AClientPlayCharacter::AClientPlayCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UDPReady = false;
	ServerPost = false;
	m_Movable = true;
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack1Asset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_AttackA.AM_AttackA'"));

	if (Attack1Asset.Succeeded())
	{
		m_AttackMontage = Attack1Asset.Object;
		m_AttackMontageArray.Add(Attack1Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	SkyAttackAsset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_SkyAttack.AM_SkyAttack'"));

	if (SkyAttackAsset.Succeeded())
	{
		m_SkyAttackMontage = SkyAttackAsset.Object;
		m_SkyAttackMontageArray.Add(SkyAttackAsset.Object);
	}
}

// Called when the game starts or when spawned
void AClientPlayCharacter::BeginPlay()
{
	Super::BeginPlay();
	JumpMaxCount = 2;

	m_AnimInst = Cast<UClientAnimInstance>(GetMesh()->GetAnimInstance());
	m_AnimInst->ChangeAnimation(ClientAnimationType::Idle);
	APlayGameMode* GameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (nullptr == GameMode || false == GameMode->IsValidLowLevel())
	{
		return;
	}

	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}
	GetCharacterMovement()->JumpZVelocity = 800.f;
	SetObjectType(EGameObjectType::Player);
	SetObjectId(Inst->ObjectIndex);
	GameMode->RegistObject(Inst->ObjectIndex, EGameObjectType::Player, this);

	ClientToReadyMessage Msg;

	Msg.ObjectIndex = Inst->ObjectIndex;
	Msg.ThreadIndex = Inst->ThreadIndex;
	Msg.SectionIndex = Inst->SectionIndex;
	GameServerSerializer Sr;
	Msg.Serialize(Sr);
	if (false != Inst->Send(Sr.GetData()))
	{
		Inst->LoginProcess_ = true;
	}

}

//void AClientPlayCharacter::AnimationStart(ClientAnimationType _Value)
//{
//	if (_Value == ClientAnimationType::Attack)
//	{
//
//	}
//}
//
//void AClientPlayCharacter::AnimationEnd(ClientAnimationType _Value)
//{
//	if (_Value == ClientAnimationType::Attack)
//	{
//		m_AnimInst->ChangeAnimation(ClientAnimationType::Idle);
//	}
//}

void AClientPlayCharacter::SendPlayerUpdatePacket()
{
	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}

	PlayerUpdateMessage UpdateMsg;
	UpdateMsg.Data.Dir = GetActorForwardVector();
	UpdateMsg.Data.Pos = GetActorLocation();
	FQuat RotData = GetActorQuat();
	UpdateMsg.Data.Rot = FVector4(RotData.X, RotData.Y, RotData.Z, RotData.W);
	UpdateMsg.Data.ObjectIndex = Inst->ObjectIndex;
	UpdateMsg.Data.SectionIndex = Inst->SectionIndex;
	UpdateMsg.Data.ThreadIndex = Inst->ThreadIndex;
	UpdateMsg.Data.SetState(m_AnimInst->GetAnimationType());
	// UpdateMsg.Data.SetState(EPlayerState::PState_Idle);

	GameServerSerializer Sr;
	UpdateMsg.Serialize(Sr);

	if (m_AnimInst->GetIsAttack() == true)
	{
		if (false == Inst->Send(Sr.GetData()))
		{
			int a = 0;
		}
	}
	else
	{
		if (false == Inst->SendTo(Sr.GetData()))
		{
			int a = 0;
		}
	}
}

// Called every frame
void AClientPlayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttTimeCheck -= DeltaTime;
	m_AnimInst->SetFullbody(m_AnimInst->GetCurveValue("FullBody"));

	APlayGameMode* GameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (nullptr == GameMode || false == GameMode->IsValidLowLevel())
	{
		return;
	}

	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}

	// 5개가 들어왔는데
	// 3번째가 디스트로이라고 봅시다.
	while (false == GetMessage()->IsEmpty())
	{
		std::shared_ptr<GameServerMessage> Message = GetMessage()->Dequeue();

		if (MessageId::LevelMove == Message->GetId<MessageId>())
		{
			ServerPost = false;
			LevelMoveReplyMessage MoveReplyMsg;
			MoveReplyMsg.ObjectIndex = Inst->ObjectIndex;
			MoveReplyMsg.SectionIndex = Inst->SectionIndex;
			MoveReplyMsg.ThreadIndex = Inst->ThreadIndex;
			// UpdateMsg.Data.SetState(EPlayerState::PState_Idle);

			GameServerSerializer Sr;
			MoveReplyMsg.Serialize(Sr);
			if (false == Inst->Send(Sr.GetData()))
			{
				int a = 0;
			}
		}
		else if (MessageId::UDPReadyOK == Message->GetId<MessageId>())
		{
			UDPReady = true;
		}
		else if (MessageId::ObjectDestroy == Message->GetId<MessageId>())
		{
			Destroy();
		}
		else if (MessageId::PlayerUpdate == Message->GetId<MessageId>())
		{
			ServerPost = true;
		}
		else 
		{
			int a = 0;
		}
	}

	//if (IsAttack == true
	//	&& AttTimeCheck <= 0.0f )
	//{
	//	IsAttack = false;
	//	bool IsCheck = false;

	//	// 1000데미지를 준다고 하겠습니다.
	//	// 클라이언트 적인 판단으로
	//	// 5번 맞춰서 3번 맞췄다.

	//	GameMode->MonsterCollisionCallBack(this, 250.0f, 160.0f, [&](AClientMonster* Monster) 
	//	{
	//		IsCheck = true;
	//		Monster->SetClientDamage(1000.0f);
	//	});

	//	if (true == IsCheck)
	//	{
	//		DebugCircle(FVector::ZeroVector, FColor::Red, 250.0f);
	//	}
	//}

	if (false == ServerPost)
	{
		return;
	}

	if (false == UDPReady)
	{
		SendPlayerUpdatePacket();
		return;
	}

	if (PrevVector == GetActorLocation())
	{
		SendPlayerUpdatePacket();
		return;
	}

	SendPlayerUpdatePacket();
	PrevVector = GetActorLocation();

}

// Called to bind functionality to input
void AClientPlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AClientPlayCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AClientPlayCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AClientPlayCharacter::JumpKey);
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ClientPlayer_MoveForward", EKeys::W));
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ClientPlayer_MoveForward", EKeys::S));
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ClientPlayer_Move", EKeys::D));
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ClientPlayer_Move", EKeys::A));

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AClientPlayCharacter::Attack); 
	PlayerInputComponent->BindAction(TEXT("Skill1"), EInputEvent::IE_Pressed, this, &AClientPlayCharacter::Skill1Key);
	PlayerInputComponent->BindAction(TEXT("Skill2"), EInputEvent::IE_Pressed, this, &AClientPlayCharacter::Skill2Key);
	PlayerInputComponent->BindAction(TEXT("Skill3"), EInputEvent::IE_Pressed, this, &AClientPlayCharacter::Skill3Key);

	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &AClientPlayCharacter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &AClientPlayCharacter::StopSprint);

	/*PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &APlayerCharacter::ZoomInKey);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::JumpKey);


	PlayerInputComponent->BindAction(TEXT("Quest"), EInputEvent::IE_Pressed, this, &APlayerCharacter::QuestKey);
	PlayerInputComponent->BindAction(TEXT("Quit"), EInputEvent::IE_Pressed, this, &APlayerCharacter::QuitKey);
	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &APlayerCharacter::InteractionKey);
	PlayerInputComponent->BindAction(TEXT("Equipment"), EInputEvent::IE_Pressed, this, &APlayerCharacter::EquipmentKey);
	PlayerInputComponent->BindAction(TEXT("Inventory"), EInputEvent::IE_Pressed, this, &APlayerCharacter::InventoryKey);*/

	// 얼마나 지속적으로 오래눌렀고 세게 눌렀다 약하게 눌렀다는 체크해야할때가 많습니다.
	// 정의 내린 키가 입력되었을대 
	//PlayerInputComponent->BindAxis("DefaultPawn_MoveForward", this, &AClientPlayCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("ClientPlayer_MoveRight", this, &AClientPlayCharacter::MoveRight);
	//PlayerInputComponent->BindAction("ClientPlayer_Move", EInputEvent::IE_Pressed, this, &AClientPlayCharacter::MoveStart);
	//PlayerInputComponent->BindAction("ClientPlayer_Move", EInputEvent::IE_Released, this, &AClientPlayCharacter::MoveEnd);

	// 얼마나 지속적으로 오래눌렀고 세게 눌렀다 약하게 눌렀다는 체크해야할때가 많습니다.
	// 정의 내린 키가 입력되었을대 
	//PlayerInputComponent->BindAxis("DefaultPawn_MoveForward", this, &AClientPlayCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("ClientPlayer_MoveRight", this, &AClientPlayCharacter::MoveRight);
	PlayerInputComponent->BindAction("ClientPlayer_Move", EInputEvent::IE_Pressed, this, &AClientPlayCharacter::MoveStart);
	PlayerInputComponent->BindAction("ClientPlayer_Move", EInputEvent::IE_Released, this, &AClientPlayCharacter::MoveEnd);

	//PlayerInputComponent->BindAction("ClientPlayer_Attack", EInputEvent::IE_Released, this, &AClientPlayCharacter::Attack);
	//PlayerInputComponent->BindAction("TestPacket0", EInputEvent::IE_Released, this, &AClientPlayCharacter::TestPacketUpdate0);

	FInputModeGameAndUI InputMode;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void AClientPlayCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= 1.5;
	
	m_IsSprint = true;
}
void AClientPlayCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= 1.5;
	m_IsSprint = false;

}
void AClientPlayCharacter::JumpKey()
{
	//LOG(TEXT("%d"), JumpCurrentCount);
	if (m_AnimInst->GetOnSky() == false || JumpCurrentCount == 1)
	{
		Jump();
		m_AnimInst->ChangeAnimation(ClientAnimationType::Jump);

		if (JumpCurrentCount == 1)
		{
			m_AnimInst->SetDoubleJump(true);
			m_AnimInst->ChangeAnimation(ClientAnimationType::DoubleJump);
		}
	}

}
void AClientPlayCharacter::Skill1Key()
{
	m_SkillIdx = 0;
	//SkillPlayAnim(m_SkillIdx);

}

void AClientPlayCharacter::Skill2Key()
{
	m_SkillIdx = 1;
	//SkillPlayAnim(m_SkillIdx);

}
void AClientPlayCharacter::Skill3Key()
{
	m_SkillIdx = 2;
	//SkillPlayAnim(m_SkillIdx);

}
bool AClientPlayCharacter::SkillPlayAnim(int32 idx)
{
	//if (m_IsInTown == false)
	//{
	//	if (m_PlayerInfo.MP > m_PlayerInfo.SkillTree[idx].RequiredMP && m_PlayerInfo.Level >= m_PlayerInfo.SkillTree[idx].RequiredLevel)
	//	{
	//		if (m_AnimInst->GetOnSky() == false && m_AnimInst->GetCanAttack() == true)
	//		{
	//			APlayGameMode* GameMode = Cast<APlayGameMode>(GetWorld()->GetAuthGameMode());

	//			if (IsValid(GameMode))
	//			{
	//				/*UPlayUIUserWidget* MainHUD = GameMode->GetMainHUD();

	//				if (IsValid(MainHUD))
	//				{
	//					UCharacterHUD* CharacterHUD = MainHUD->GetCharacterHUD();

	//					if (IsValid(CharacterHUD))
	//					{
	//						TArray<USkillImageWidget*> SkillArray = CharacterHUD->GetSkillArray();

	//						if (SkillArray[idx]->GetCoolTimeOn() == true)
	//						{
	//							if (!m_AnimInst->Montage_IsPlaying(m_SkillMontageArray[idx]))
	//							{
	//								m_AnimInst->Montage_SetPosition(m_SkillMontageArray[idx], 0.f);
	//								m_AnimInst->Montage_Play((m_SkillMontageArray[idx]));
	//								SkillArray[idx]->SetCoolTimePercent(1.f, m_PlayerInfo.SkillTree[idx].CoolTime);
	//								return true;
	//							}
	//						}
	//					}
	//				}*/
	//			}
	//		}
	//	}
	//}
	return false;
}
//XX
void AClientPlayCharacter::SetChatTypeOne()
{
	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	//UE_LOG(ClientLog, Log, TEXT("Player FName :: %d"), Inst->ObjectIndex);

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(100.0f),
		Params);

	if (bResult)
	{
		//UE_LOG(ClientLog, Log, TEXT("Character FName :: %s"), *HitResult.Actor->GetName());

		AClientOtherCharacter* OtherPlayer = Cast<AClientOtherCharacter>(HitResult.Actor);
		if(OtherPlayer)
			Inst->TargetObjectIndex = OtherPlayer->ObjectIndex;
		//UE_LOG(ClientLog, Log, TEXT("Character FName :: %d"), Inst->TargetObjectIndex);
	}

	Inst->SetMsgType(EChatMessageType::ONEPLAYER);
}

//ZZ
void AClientPlayCharacter::SetChatTypeInSec()
{
	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}

	Inst->SetMsgType(EChatMessageType::INSECTION);
}
//CC
void AClientPlayCharacter::SetChatTypeAll()
{
	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}
	Inst->SetMsgType(EChatMessageType::ALL);
}

void AClientPlayCharacter::MoveForward(float _Rate)
{
	if (0.0f == _Rate)
	{
		return;
	}


	AddControllerYawInput(LookZ(FVector(1.0f, -1.0f, 0.0f).GetSafeNormal() * _Rate, 0.1f));

	AddMovementInput(FVector(1.0f, -1.0f, 0.0f).GetSafeNormal(), _Rate);
	if (m_AnimInst->GetIsAttack() == false)
	{
		m_AnimInst->ChangeAnimation(ClientAnimationType::Move);
		//LOG(TEXT("MOVEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"));
	}

}

void AClientPlayCharacter::MoveRight(float _Rate)
{
	if (0.0f == _Rate)
	{
		return;
	}


	AddControllerYawInput(LookZ(FVector(1.0f, 1.0f, 0.0f).GetSafeNormal() * _Rate, 0.1f));

	AddMovementInput(FVector(1.0f, 1.0f, 0.0f).GetSafeNormal(), _Rate);

	if (m_AnimInst->GetIsAttack() == false)
	{
		m_AnimInst->ChangeAnimation(ClientAnimationType::Move);
		//LOG(TEXT("MOVEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"));

	}

}
//void AClientPlayCharacter::MoveRight(float _Rate) 
//{
//	if (false == UDPReady)
//	{
//		return;
//	}
//
//	if (m_AnimInst->GetAnimationType() == ClientAnimationType::Attack)
//	{
//		return;
//	}
//
//	if (0.0f == _Rate)
//	{
//		return;
//	}
//
//	AddControllerYawInput(LookZ(FVector(1.0f, 1.0f, 0.0f).GetSafeNormal() * _Rate, 0.1f));
//
//	AddMovementInput(FVector(1.0f, 1.0f, 0.0f).GetSafeNormal(), _Rate);
//	m_AnimInst->ChangeAnimation(ClientAnimationType::Move);
//}
//
//void AClientPlayCharacter::MoveForward(float _Rate) 
//{
//	if (false == UDPReady)
//	{
//		return;
//	}
//
//	if (m_AnimInst->GetAnimationType() == ClientAnimationType::Attack)
//	{
//		return;
//	}
//	if (0.0f == _Rate)
//	{
//		return;
//	}
//
//
//	AddControllerYawInput(LookZ(FVector(1.0f, -1.0f, 0.0f).GetSafeNormal() * _Rate, 0.1f));
//
//	AddMovementInput(FVector(1.0f, -1.0f, 0.0f).GetSafeNormal(), _Rate);
//	//m_AnimInst->ChangeAnimation(ClientAnimationType::Move);
//}

void AClientPlayCharacter::MoveStart()
{
	if (false == UDPReady)
	{
		return;
	}

	if (m_Movable && m_AnimInst->GetIsAttack() == false)
	{
		m_AnimInst->ChangeAnimation(ClientAnimationType::Move);
	}
}

void AClientPlayCharacter::MoveEnd()
{
	if (false == UDPReady)
	{
		return;
	}

	if (m_Movable && m_AnimInst->GetIsAttack() == false)
	{
		m_AnimInst->ChangeAnimation(ClientAnimationType::Idle);
	}
}

void AClientPlayCharacter::Attack() 
{
	if (false == UDPReady)
	{
		return;
	}

	// 화면을 바라보는건 클라이언트 뿐입니다.

	// LookZ(FVector(1.0f, -1.0f, 0.0f).GetSafeNormal(), 0.1f);
	if (m_AnimInst->GetCanAttack())
	{
		m_AnimInst->SetIsAttack(true);
		if (!m_AnimInst->GetOnSky())			//하늘에 있으면 땅에서 하는 콤보 공격 불가
		{
			if (m_CurrentCombo == 0)
			{
				m_AnimInst->Montage_Play(m_AttackMontage);
				m_AnimInst->ChangeAnimation(ClientAnimationType::Attack1);

			}
			else
			{


				m_AnimInst->Montage_JumpToSection(m_AnimInst->GetAttackMontageSectionName(m_CurrentCombo + 1 % 5));
				if(m_CurrentCombo == 1)
					m_AnimInst->ChangeAnimation(ClientAnimationType::Attack2);
				else if (m_CurrentCombo == 2)
					m_AnimInst->ChangeAnimation(ClientAnimationType::Attack3);
				else if (m_CurrentCombo == 3)
					m_AnimInst->ChangeAnimation(ClientAnimationType::Attack4);
			} 


			m_CurrentCombo++;

			m_AnimInst->SetCanAttack(false);
		}
		else
		{

			//LOG(TEXT("SKY ATTACK"));
			if (!m_AnimInst->GetDoubleJump())
			{
				m_AnimInst->Montage_Play(m_SkyAttackMontage);
				m_AnimInst->ChangeAnimation(ClientAnimationType::JumpAttack);
			}
			else
				m_AnimInst->ChangeAnimation(ClientAnimationType::SlamAttack);
			m_AnimInst->SetCanAttack(false);
		}
	}

	//AddControllerYawInput(LookZ(MouseVectorToWorldVector() - GetActorLocation(), 1.0F));
	SendPlayerUpdatePacket();
}


FVector AClientPlayCharacter::MouseVectorToWorldVector()
{
	if (false == UDPReady)
	{
		return FVector(TNumericLimits<float>::Max(), TNumericLimits<float>::Max(), TNumericLimits<float>::Max());
	}

	APlayerController* PC = Cast<APlayerController>(GetController());

	if (nullptr == PC && PC->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > nullptr Controller"), __FUNCTION__, __LINE__);
		// 정한거다. 
		return FVector(TNumericLimits<float>::Max(), TNumericLimits<float>::Max(), TNumericLimits<float>::Max());
	}


	FHitResult TraceHitResult;

	if (false == PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult))
	{
		//     월드 좌표이기 때문에
		return FVector(TNumericLimits<float>::Max(), TNumericLimits<float>::Max(), TNumericLimits<float>::Max());
	}
	
	return TraceHitResult.Location;
}

void AClientPlayCharacter::SetTimeDefaultTimeDilation()
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(1.f);

}

void AClientPlayCharacter::SetTimeDillation()
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(0.5f);
	GetWorld()->GetTimerManager().SetTimer(TimeDillationHandle,
		this, &AClientPlayCharacter::SetTimeDefaultTimeDilation, 1.f, false, 0.25f);
}
//void AClientPlayCharacter::TestPacketUpdate0()
//{
//	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
//
//	if (nullptr == Inst || false == Inst->IsValidLowLevel())
//	{
//		return;
//	}
//
//	if (false == Inst->GetClientMode())
//	{
//		return;
//	}
//
//#include "../Message/ServerToClient.h"
//	std::shared_ptr<MonsterUpdateMessage> Message = std::make_shared<MonsterUpdateMessage>();
//	Message->ObjectID = 100;
//	Message->Pos = FVector(500.0f, 500.0f, 200.0f);
//	Message->MonsterType = 0;
//	Inst->PushClientMessage(Message);
//
//}