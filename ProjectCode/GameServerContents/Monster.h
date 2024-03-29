#pragma once
#include <GameServerCore\GameServerActor.h>
#include "ServerToClient.h"
#include "Monster.h"



// 설명 :
class Monster : public GameServerActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:
	MonsterUpdateMessage Message_;
	GameServerSerializer Serializer_;

	GameServerActor* Target;

	float UpdateTime;
	float AttTime;

	float DeleteTime;

	bool IsDeath;
	// void SelfUpdateMessage();
	GameServerSerializer& GetSerializeMonsterUpdateMessage();
	void BroadcastingMonsterUpdateMessage(bool UDP = true);

	float DelayAttackTime;
	bool CanAttack;
	bool OneTimeAttack;
	GameServerCollision* PlayerSensorCollision;
	GameServerCollision* HitCollision;
	GameServerCollision* AttackCollision;

private:
	void Update(float _Time) override;

	void SectionInitialize() override;
	void TCPSessionInitialize() override;
	void UDPSessionInitialize() override;

	bool InsertSection() override;

	// 객체로서 삭제되는 것
	void DeathEvent() override;

public:
	void ChangeState(EMonsterState _State);

	void StateUpdate(float _DeltaTime);

	void IdleStart();
	void TraceStart();
	void AttStart();
	void DeathStart();
	void IdleUpdate(float _DeltaTime);
	void TraceUpdate(float _DeltaTime);
	void AttUpdate(float _DeltaTime);
	void DeathUpdate(float _DeltaTime);

};

