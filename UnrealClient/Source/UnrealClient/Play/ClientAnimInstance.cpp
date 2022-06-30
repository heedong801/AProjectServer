#include"ClientAnimInstance.h"
#include "ClientPlayCharacter.h"


UClientAnimInstance::UClientAnimInstance()
	: m_Dir(0), m_Speed(0), m_CanAttack(true), m_OnSky(false)
{
}

void UClientAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UClientAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AClientPlayCharacter* Player = Cast<AClientPlayCharacter>(TryGetPawnOwner());

	//LOG(TEXT("%f"), Player->GetActorScale3D().Size());
	if (Player)
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();

		if (Movement)
		{
			m_Speed = Movement->Velocity.Size();
			//LOG(TEXT("%f"), m_Speed);
			m_OnSky = Movement->IsFalling();

			//LOG(TEXT("%f"), Player->GetCharacterMovement()->GravityScale);
			//LOG(TEXT("%f"), Player->GetCharacterMovement()->JumpZVelocity);

			if (!m_OnSky)
			{
				m_DoubleJump = false;
				Player->GetCharacterMovement()->GravityScale = 1.f;

			}
			else
			{
				


				//Player->GetCharacterMovement()->GravityScale = 3.f;
			}

		}
	}
}

void UClientAnimInstance::AnimNotify_AttackCombo()
{
	//LOG(TEXT("true : %s"), *GetSkelMeshComponent()->GetName());


	m_CanAttack = true;
}

void UClientAnimInstance::AnimNotify_HitDamage()
{
	//AClientPlayCharacter* Player = Cast<AClientPlayCharacter>(TryGetPawnOwner());

	//if (Player)
	//	Player->HitDamage();
}

FName UClientAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}


void UClientAnimInstance::SetFullbody(float useFullbody)
{
	if (useFullbody > 0.f)
		m_UseFullbody = true;
	else
		m_UseFullbody = false;
}

void UClientAnimInstance::AnimNotify_AddGravity()
{
	////LOG(TEXT("AnimNotify_AddGravity"));
	AClientPlayCharacter* Player = Cast<AClientPlayCharacter>(TryGetPawnOwner());

	if (Player)
	{
		Player->SetTimeDillation();
		Player->GetCharacterMovement()->Velocity.X = 0.f;
		Player->GetCharacterMovement()->Velocity.Y = 0.f;
		//Player->SetActorLocation( FVector(Player->GetActorLocation().X, Player->GetActorLocation().Y, Player->GetActorLocation().Z + 200)) ;

		GetWorld()->GetTimerManager().SetTimer(m_AddGravityTimer,
			this, &UClientAnimInstance::AddGravity, 1.f, false, 0.1f);
		//Player->GetCharacterMovement()->Velocity.Z = 0.f;
		//Player->GetCharacterMovement()->GravityScale = 200.0f;
		//LOG(TEXT("%f %f %f"), Player->GetCharacterMovement()->Velocity.X, Player->GetCharacterMovement()->Velocity.Y, Player->GetCharacterMovement()->Velocity.Z);
	}
}

void UClientAnimInstance::AddGravity()
{
	AClientPlayCharacter* Player = Cast<AClientPlayCharacter>(TryGetPawnOwner());
	if (Player)
		Player->GetCharacterMovement()->GravityScale = 200.0f;

}


void UClientAnimInstance::AnimNotify_SlamEnd()
{
	////LOG(TEXT("AnimNotify_SlamEnd"));

	//AWukong* Wukong = Cast<AWukong>(TryGetPawnOwner());
	//Wukong->SlamDamage();
}

void UClientAnimInstance::AnimNotify_AttackEnd()
{
	//LOG(TEXT("true : %s"), *GetSkelMeshComponent()->GetName());

	AClientPlayCharacter* Player = Cast<AClientPlayCharacter>(TryGetPawnOwner());

	if (Player)
	{
		m_CanAttack = true;
		Player->SetCurrentCombo(0);
		//Player->SetMovable(true);
		//Player->CameraArmYawReset();

	}

}


void UClientAnimInstance::AnimNotify_UseSkill()
{

	//m_CanAttack = false;
	//AClientPlayCharacter* Player = Cast<AClientPlayCharacter>(TryGetPawnOwner());

	//if (Player)
	//{
	//	//LOG(TEXT("C"));
	//	Player->SetMovable(false);

	//	Player->UseSkill(Player->GetSkillIdx());
	//}
}

void UClientAnimInstance::ChangeAnimation(ClientAnimationType _Type)
{
	if (CurrentAnimationType_ == _Type)
	{
		return;
	}

	CurrentAnimationType_ = _Type;
}