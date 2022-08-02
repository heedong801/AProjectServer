#pragma once
#include <GameServerCore\GameServerActor.h>
#include "ServerAndClient.h"
#include <GameServerNet\RedisConnecter.h>
#include <GameServerNet\DBConnecter.h>

// ���� :
class ContentsUserData;
class Player : public GameServerActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

private:
	std::shared_ptr<RedisConnecter> GetBaseRankConntor() 
	{
		return RedisConnecter::GetConnector(0);
	}
	std::shared_ptr<DBConnecter> GetDBConnector()
	{
		return DBConnecter::GetConnector(0);
	}
	//std::shared_ptr<RedisConnecter> GetRegulerRankConntor()
	//{
	//	return RedisConnecter::GetConnector(1);
	//}

public:
	void MessageCheck();
	void AttackCollisionCheck(GameServerCollision* _Collision);
	void ClientToReadyMessageProcess(std::shared_ptr<class ClientToReadyMessage> _Message);
	void PlayerUpdateMessageProcess(std::shared_ptr<class PlayerUpdateMessage> _Message);
	void LevelMoveReplyMessageProcess(std::shared_ptr<class LevelMoveReplyMessage> _Message);
	void ChatMessageProcess(std::shared_ptr<class ChatMessage> _Message);


protected:
	PlayerUpdateMessage& GetPlayerUpdateMessage();
	GameServerSerializer& GetSerializePlayerUpdateMessage();

	void SelfTCPMessage(std::vector<unsigned char> data);
	void BroadcastingPlayerUpdateMessage();

private:
	class Portal* PortalPtr;

	// std::shared_ptr<GameServerCollision> HitCollision;
	GameServerCollision* HitCollision;
	GameServerCollision* SlamCollision;
	GameServerCollision* AttackCollision;

	GameServerCollision* CurrentCollision;
	float AttTime;
	float DelayAttackTime;
	bool IsAttack;
	PlayerUpdateMessage Message_;
	GameServerSerializer Serializer_;

	std::shared_ptr<ContentsUserData> UserData;

	EPlayerState PrevPlayerState;
	bool UDPReady_;

	void Update(float _Time) override;

	void SectionInitialize() override;
	void TCPSessionInitialize() override;
	void UDPSessionInitialize() override;

	bool InsertSection() override;

	// ��ü�μ� �����Ǵ� ��
	void DeathEvent() override;

	// �̰� ���� ���ǿ����� �����Ǳ� �����̰�
	// ������ �޸𸮰� �����Ǳ� ������ ȣ��Ǵ°�
	void DisConnect();
	void DelayAttack(EPlayerState state);

};

