// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientMonster.h"
#include "ObjectMessageComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Global/ClientGameInstance.h"
#include "../Play/PlayGameMode.h"
#include "Animation/AnimMontage.h"
#include "MonsterAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "../UnrealClient.h"

#include "Kismet/KismetMathLibrary.h"

void AClientMonster::AnimationStart(NonePlayerAnimationType _Value) 
{
//#ifdef ENABLE_DRAW_DEBUG
//	if (_Value == NonePlayerAnimationType::Attack)
//	{
//		DrawDebugSphere(GetWorld(), GetActorLocation() + (GetActorForwardVector() * 100.0f), 200.0f, 10, FColor::Red, false, 0.5f, 0, 5.0f);
//	}
//#endif
}

void AClientMonster::AnimationEnd(NonePlayerAnimationType _Value) 
{
	if (_Value == NonePlayerAnimationType::Death)
	{
		Destroyed();
		Destroy();
	}
	if (_Value == NonePlayerAnimationType::Attack)
	{
		//GetClientAnimInstance()->ChangeAnimation(NonePlayerAnimationType::Idle);

//#include "../Message/ServerToClient.h"
//		std::shared_ptr<MonsterUpdateMessage> Message = std::make_shared<MonsterUpdateMessage>();
//		Message->ObjectID = GetObjectId();
//		Message->Pos = GetActorLocation();
//		Message->UpdateType = EMonsterState::MState_Idle;
//		Inst->PushClientMessage(Message);
	}
}

void AClientMonster::BeginPlay() 
{
	Super::BeginPlay();

	AnimationInst = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());


	State_ = EMonsterState::MState_Idle;

	GetClientAnimInstance()->AddEndFunctionBind(std::bind(&AClientMonster::AnimationEnd, this, std::placeholders::_1));

	GetClientAnimInstance()->AddStartFunctionBind(std::bind(&AClientMonster::AnimationStart, this, std::placeholders::_1));
	Ratio = 0.0f;

	//UE_LOG(ClientLog, Error, TEXT("%S(%u) > BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"), __FUNCTION__, __LINE__);

}

void AClientMonster::ObjectInit() 
{
	CurrentUpdateData.Pos = GetActorLocation();
	Ratio = 0.0f;

	ClientObjectInit();
}

void AClientMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UClientGameInstance* GameInst = Cast<UClientGameInstance>(GetGameInstance());

	//if (true == GameInst->GetClientMode())
	//{
	//	// 클라이언트에서 만든 인공지능으로 돌아가는 겁니다.
	//	ClientUpdate(DeltaTime);
	//	return;
	//}

	// 5개가 들어왔는데
	// 3번째가 디스트로이라고 봅시다.
	while (false == GetMessage()->IsEmpty())
	{
		std::shared_ptr<GameServerMessage> Message = GetMessage()->Dequeue();

		if (DeathFlag == true)
		{
			if (MessageId::ObjectDestroy == Message->GetId<MessageId>())
			{
				//UE_LOG(ClientLog, Error, TEXT("%S(%u) > ObjectDestoZZZZZZZZZZZZZZZZZZZZZZZZZZZZy"), __FUNCTION__, __LINE__);
			}
			return;
		}
		else
		{
			if (MessageId::MonsterUpdate == Message->GetId<MessageId>())
			{
				std::shared_ptr<MonsterUpdateMessage> UpdateMessage = std::static_pointer_cast<MonsterUpdateMessage>(Message);

				if (nullptr == UpdateMessage)
				{
					continue;
				}

				State_ = static_cast<EMonsterState>(UpdateMessage->Data.State);

				switch (State_)
				{
				case EMonsterState::NONE:
					break;
				case EMonsterState::MState_Idle:
					GetClientAnimInstance()->ChangeAnimation(NonePlayerAnimationType::Idle);
					break;
				case EMonsterState::MState_Trace:
					GetClientAnimInstance()->ChangeAnimation(NonePlayerAnimationType::Move);
					break;
				case EMonsterState::MState_Att:
					GetClientAnimInstance()->ChangeAnimation(NonePlayerAnimationType::Attack);
					break;
				case EMonsterState::MState_Death:
					GetClientAnimInstance()->ChangeAnimation(NonePlayerAnimationType::Death);
					DeathFlag = true;
					break;
				case EMonsterState::MAX:
					break;
				default:
					break;
				}

				UpDataData.Add(UpdateMessage->Data);

				LookTargetZ(UpdateMessage->Data.Dir);
				SetActorLocation(UpdateMessage->Data.Pos, false, nullptr, ETeleportType::ResetPhysics);
			}
		}
	}

	//FVector Pos = GetActorLocation();

	//if (0 != UpDataData.Num())
	//{
	//	if (UpDataData[0].State == static_cast<int>(EMonsterState::MState_Idle))
	//	{
	//		UpDataData.Pop();
	//		return;
	//	}

	//	FVector4 LookDir = UpDataData[0].Dir;
	//	LookTargetZ(LookDir);

	//	Ratio += DeltaTime * 1.5f;

	//	if (1.0f <= Ratio)
	//	{
	//		Ratio = 1.0f;
	//	}

	//	Pos = FMath::Lerp(CurrentUpdateData.Pos, UpDataData[0].Pos, Ratio);

	//	if (1.0f <= Ratio)
	//	{
	//		CurrentUpdateData = UpDataData[0];
	//		UpDataData.Pop();
	//		Ratio = 0.0f;
	//	}
	//}

	//SetActorLocation(Pos, false, nullptr, ETeleportType::None);
}



void AClientMonster::SetClientDamage(float _Damage)
{
	UClientGameInstance* Inst = Cast<UClientGameInstance>(GetGameInstance());

	// UI로 보여줘야 하잖아요.
	Info.Hp -= _Damage;

	if (false == Inst->GetClientMode())
	{
		return;
	}

	if (0 >= Info.Hp)
	{
#include "../Message/ServerToClient.h"
		std::shared_ptr<ObjectDestroyMessage> Message = std::make_shared<ObjectDestroyMessage>();
		Message->ObjectID = GetObjectId();
		Inst->PushClientMessage(Message);
	}
}


void AClientMonster::ClientUpdate(float _DelataTime)
{
	//switch (State_)
	//{
	//case EMonsterState::MState_Idle:
	//	Idle(_DelataTime);
	//	break;
	//case EMonsterState::MState_Trace:
	//	Trace(_DelataTime);
	//	break;
	//case EMonsterState::MState_Att:
	//	Att(_DelataTime);
	//	break;
	//default:
	//	break;
	//}
}


void AClientMonster::ClientObjectInit() 
{
//	UClientGameInstance* Inst = Cast<UClientGameInstance>(GetGameInstance());
//
//	if (true == Inst->GetClientMode())
//	{
//		// 클라이언트에서 만든 인공지능으로 돌아가는 겁니다.
//		Info.Att = 10;
//		Info.Hp = 100;
//		Info.LookRange = 1500;
//		Info.TraceRange = 800;
//		Info.AttRange = 150;
//		Info.Speed = 200;
//
//
//#include "../Message/ServerToClient.h"
//		std::shared_ptr<MonsterUpdateMessage> Message = std::make_shared<MonsterUpdateMessage>();
//		Message->ObjectID = GetObjectId();
//		Message->Pos = GetActorLocation();
//		Message->UpdateType = EMonsterState::MState_Idle;
//		Inst->PushClientMessage(Message);
//	}
}