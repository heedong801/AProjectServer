#include "PreCompile.h"
#include "Player.h"
#include "Portal.h"
#include "ClientToServer.h"
#include "ServerToClient.h"
#include "GameServerCore\GameServerCore.h"
#include "GameServerBase\GameServerThread.h"
#include "Monster.h"
#include <GameServerNet\TCPSession.h>
#include "ContentsSystemEnum.h"
#include "ContentsUserData.h"
#include "CharacterTable.h"
#include "ContentsEnum.h"
#include "GameServerBase\GameServerDebug.h"
#include <GameServerCore\GameServerSection.h>
#include <GameServerCore\DBQueue.h>


Player::Player()
	: UDPReady_(false)
	, PortalPtr(nullptr)
	, HitCollision(nullptr)
	, SlamCollision(nullptr)
	, AttackCollision(nullptr)
	, CurrentCollision(nullptr)
	, IsAttack(false)
	, PrevPlayerState(EPlayerState::NONE)
{
}

Player::~Player() 
{

	if (nullptr != HitCollision)
	{
		HitCollision->Death();
		HitCollision = nullptr;
	}
	if (nullptr != AttackCollision)
	{
		AttackCollision->Death();
		AttackCollision = nullptr;
	}
	if (nullptr != SlamCollision)
	{
		SlamCollision->Death();
		SlamCollision = nullptr;
	}
}

void Player::AttackCollisionCheck(GameServerCollision* _Collision)
{
	std::vector<GameServerCollision*> Result;

	if (true == _Collision->CollisionCheckResult(CollisionCheckType::SPHERE, ECollisionGroup::MONSTER, CollisionCheckType::SPHERE, Result))
	{
		for (auto el : Result)
		{
			Monster* MonsterPtr = el->GetOwnerActorConvert<Monster>();

			if (nullptr == MonsterPtr)
			{
				GameServerDebug::AssertDebugMsg("몬스터에 잘못된 객체가 들어가 있었습니다.");
				return;
			}

			{
				const std::list<std::shared_ptr<GameServerActor>>& AllOtherPlayer = GetSection()->GetPlayableActor();

				GetItemMessage Message;
				GameServerRandom Random;
				Message.ItemData.ObjectIndex = GetIndex();
				Message.ItemData.ItemIndex = Random.RandomInt(0, 7);

				GameServerSerializer Sr;
				Message.Serialize(Sr);

				for (auto& OtherActor : AllOtherPlayer)
				{
					// 나는 제외
					if (GetIndex() == OtherActor->GetIndex())
					{
						continue;
					}
					std::shared_ptr<Player> OtherPlayer = std::dynamic_pointer_cast<Player>(OtherActor);
					OtherPlayer->GetTCPSession()->Send(Sr.GetData());
				}
			}

			// 주위에 있는 다른 액터들에게 보내야하는 메세지가 됩니다.
			MonsterPtr->ChangeState(EMonsterState::MState_Death);
		}
		
	}
}

void Player::PlayerUpdateMessageProcess(std::shared_ptr<class PlayerUpdateMessage> _Message)
{
	// 이게 만약 처음으로 날아온 메세지라면.
	// 너한테 쏠수 있게 되었다.

	if (false == UDPReady_)
	{
		UDPReady_ = true;
		UDPReadyOKMessage Msg;
		Msg.Code = EGameServerCode::OK;
		Msg.ObjectIndex = GetIndex();
		GameServerSerializer Sr;
		Msg.Serialize(Sr);

		// "SELECT Idx, NickName, UserIndex, ATT, HP, LastSectionid, LastSectionPosx, LastSectionPosy, LastSectionPosz FROM userver2.characterinfo WHERE NickName = ? LIMIT 1"
		GetTCPSession()->Send(Sr.GetData());

		// GetTCPSession()->Send("SELECT Idx, NickName, UserIndex, ATT, HP, LastSectionid, LastSectionPosx, LastSectionPosy, LastSectionPosz FROM userver2.characterinfo WHERE NickName = ? LIMIT 1");
		return;
	}

	Message_.Data = _Message->Data;
	SetPos(_Message->Data.Pos);
	SetDir(_Message->Data.Dir);
	
	// (_Message->Data.Pos - _Message->Data.Pos).Length2D();
	

	DelayAttack(Message_.Data.GetState<EPlayerState>());

	BroadcastingPlayerUpdateMessage();
}

// 클라이언트한테서 연락이 왔다.
void Player::ClientToReadyMessageProcess(std::shared_ptr<ClientToReadyMessage> _Message)
{
	// 너무 중요해서 tcp로 날린다.
	//// 주위 플레이어 패킷 보냄
	{
		const std::list<std::shared_ptr<GameServerActor>>& AllOtherPlayer = GetSection()->GetPlayableActor();

		PlayersUpdateMessage Message;
		GameServerSerializer Sr;

		for (auto& OtherActor : AllOtherPlayer)
		{
			// 나는 제외
			if (GetIndex() == OtherActor->GetIndex())
			{
				continue;
			}

			std::shared_ptr<Player> OtherPlayer = std::dynamic_pointer_cast<Player>(OtherActor);

			OtherPlayer->GetSerializePlayerUpdateMessage();
			Message.Datas.push_back(OtherPlayer->Message_.Data);
		}

		// 주변 캐릭터들 전부다 나한테 쏜다.
		Message.Serialize(Sr);
		GetTCPSession()->Send(Sr.GetData());
		BroadcastingPlayerUpdateMessage();
	}

	SelfTCPMessage(GetSerializePlayerUpdateMessage().GetData());
}


void Player::ChatMessageProcess(std::shared_ptr<class ChatMessage> _Message)
{
	GameServerSerializer Sr;
	_Message->Serialize(Sr);

	SelfTCPMessage(Sr.GetData());
}

void Player::LevelMoveReplyMessageProcess(std::shared_ptr<class LevelMoveReplyMessage> _Message)
{
	if (nullptr == PortalPtr)
	{
		GameServerDebug::AssertDebugMsg("포탈에 잘못된 객체가 들어가 있었습니다.");
		return;
	}

	LevelMoveMessage Msg;
	Msg.ObjectIndex = GetIndex();
	Msg.SectionIndex = GetSectionIndex();
	Msg.ThreadIndex = GetThreadIndex();
	Msg.MoveLevel = PortalPtr->LinkSection->GetNameCopy();
	GameServerSerializer Sr;
	Msg.Serialize(Sr);
	GetSection()->TCPBroadcasting(Sr.GetData(), GetIndex());

	GetSection()->SectionMove(DynamicCast<GameServerActor>(), PortalPtr->LinkSection);
	PortalPtr = nullptr;
}

void Player::Update(float _DeltaTime) 
{
	MessageCheck();

	if (nullptr == AttackCollision)
	{
		return;
	}

	AttackCollision->SetPivot(GetDir() * 105.f);

	//Attack Check
	if (IsAttack && GetAccTime() - AttTime >= DelayAttackTime)
	{
		AttackCollisionCheck(CurrentCollision);
		AttTime = 0;
		IsAttack = false;
	}


	if (0 == (static_cast<int>(GetAccTime()) % 10) )
	{
		// DBQueue::Queue(std::bind(_ChildFunction, std::dynamic_pointer_cast<ChildThreadHandler>(this->shared_from_this())));

		std::string Name = UserData->SelectData.NickName;

		DBQueue::Queue([=]
		{
			std::shared_ptr<RedisConnecter> Connecter = GetBaseRankConntor();
			RedisCommend::ZADD MyAdd = RedisCommend::ZADD("UserRank", 10000, Name);
			MyAdd.Process(*Connecter);
		});
		// dbqueue
	}

	if (IsFrame(10))
	{
		if (nullptr == HitCollision)
		{
			return;
		}

		static std::vector<GameServerCollision*> Result;
		// 충돌 했어 안했어?

		if (true == HitCollision->CollisionCheckResult(CollisionCheckType::SPHERE, ECollisionGroup::POTAL, CollisionCheckType::SPHERE, Result))
		{
			PortalPtr = Result[0]->GetOwnerActorConvert<Portal>();

			if (nullptr == PortalPtr)
			{
				GameServerDebug::AssertDebugMsg("포탈에 잘못된 객체가 들어가 있었습니다.");
				return;
			}

			// 날아오는 패킷들도 다 무시해야죠.


			// 주위에 있는 다른 액터들에게 보내야하는 메세지가 됩니다.
			LevelMoveMessage Msg;
			Msg.ObjectIndex = GetIndex();
			Msg.SectionIndex = GetSectionIndex();
			Msg.ThreadIndex = GetThreadIndex();
			Msg.MoveLevel = PortalPtr->LinkSection->GetNameCopy();
			GameServerSerializer Sr;
			Msg.Serialize(Sr);
			// GetSection()->TCPBroadcasting(Sr.GetData(), GetIndex());

			// Off();

			GetTCPSession()->Send(Sr.GetData());


			HitCollision->Death();
			HitCollision = nullptr;
			AttackCollision->Death();
			AttackCollision = nullptr;
			SlamCollision->Death();
			SlamCollision = nullptr;

		}

		Result.clear();

	}

	// 버프 디버프

}

PlayerUpdateMessage& Player::GetPlayerUpdateMessage()
{
	Message_.Data.Dir = GetDir();
	Message_.Data.Pos = GetPos();

	return Message_;
}

GameServerSerializer& Player::GetSerializePlayerUpdateMessage()
{
	Message_.Data.Dir = GetDir();
	Message_.Data.Pos = GetPos();

	Serializer_.Reset();

	Message_.Serialize(Serializer_);

	return Serializer_;
}

void Player::BroadcastingPlayerUpdateMessage() 
{
	GetSection()->UDPBroadcasting(GetSerializePlayerUpdateMessage().GetData(), GetIndex());
}

//void Player::SelfUpdateMessage(std::vector<unsigned char> data)
//{
//	GetTCPSession()->Send(data);
//}

void Player::SelfTCPMessage(std::vector<unsigned char> data)
{
	GetTCPSession()->Send(data);
}

bool Player::InsertSection() 
{
	if (nullptr == UserData)
	{
		GameServerDebug::AssertDebugMsg("UserData Setting Is Nullptr");
		return false;
	}

	Message_.Data.ObjectIndex = GetIndex();
	Message_.Data.SectionIndex = GetSectionIndex();
	Message_.Data.ThreadIndex = GetThreadIndex();
	
	// SetPos({200, 0.0f, 0.0f});

	// 섹션 입장 패킷 보냄
	{
		SectionInsertResultMessage Msg;
		Msg.Code = EGameServerCode::OK;
		Msg.UDPPort = GetUDPPort();
		Msg.ObjectIndex = GetIndex();
		Msg.SectionIndex = GetSectionIndex();
		Msg.ThreadIndex = GetThreadIndex();
		Msg.MoveLevel = GetSection()->GetNameCopy();
		GameServerSerializer Sr;
		Msg.Serialize(Sr);
		GetTCPSession()->Send(Sr.GetData());
	}

	SetPos(FVector4::ZeroVector);

	CurrentCollision = AttackCollision;
	// 클라이언트가 나는 준비가 됐다.



	GameServerDebug::LogInfo("Select Result OK Send");

	return true;
}

void Player::SectionInitialize() 
{
	// GetSection();
	if (nullptr == HitCollision)
	{
		HitCollision = GetSection()->CreateCollision(ECollisionGroup::PLAYER, this);
		HitCollision->SetScale({ 50.0f, 50.0f, 50.0f });
	}
	if (nullptr == AttackCollision)
	{
		AttackCollision = GetSection()->CreateCollision(ECollisionGroup::PLAYER, this);
		AttackCollision->SetScale({ 125.0f, 125.0f, 100.0f });
	}
	if (nullptr == SlamCollision)
	{
		SlamCollision = GetSection()->CreateCollision(ECollisionGroup::PLAYER, this);
		SlamCollision->SetScale({ 500.0f, 500.0f, 2500.0f });
	}
	UDPReady_ = false;
}

void Player::TCPSessionInitialize() 
{
	UserData = GetTCPSession()->GetLink<ContentsUserData>(EDataIndex::USERDATA);

	if (nullptr == UserData)
	{
		GameServerDebug::AssertDebugMsg("UserData Setting Is Nullptr");
		return;
	}
}

void Player::UDPSessionInitialize()
{

	int a = 0;
}

void Player::DeathEvent()
{
	// GetSession()->UnregisterSession();
	{
		const std::list<std::shared_ptr<GameServerActor>>& AllOtherPlayer = GetSection()->GetPlayableActor();

		ObjectDestroyMessage Message;
		Message.ObjectID = GetIndex();

		GameServerSerializer Sr;
		Message.Serialize(Sr);

		for (auto& OtherActor : AllOtherPlayer)
		{
			// 나는 제외
			if (GetIndex() == OtherActor->GetIndex())
			{
				continue;
			}
			std::shared_ptr<Player> OtherPlayer = std::dynamic_pointer_cast<Player>(OtherActor);
			OtherPlayer->GetTCPSession()->Send(Sr.GetData());
		}
	}
	
	/*PlayerDestroyMessage Message;
	GameServerSerializer Sr;
	Message.Serialize(Sr);
	GetTCPSession()->Send(Sr.GetData());*/
}

void Player::DisConnect()
{
	//// 주위 플레이어 패킷 보냄

}

void Player::DelayAttack(EPlayerState state)
{
	if (IsAttack == false)
	{
		switch (state)
		{
		case EPlayerState::PState_Att1:
			if (PrevPlayerState == EPlayerState::PState_Att1)
				return;
			AttTime = GetAccTime();
			GameServerDebug::Log(LOGTYPE::LOGTYPE_ERROR, "Attack1");
			IsAttack = true;
			CurrentCollision = AttackCollision;
			DelayAttackTime = 0.2f;
			PrevPlayerState = EPlayerState::PState_Att1;
			break;
		case EPlayerState::PState_Att2:
			if (PrevPlayerState == EPlayerState::PState_Att2)
				return;
			GameServerDebug::Log(LOGTYPE::LOGTYPE_ERROR, "Attack2");

			AttTime = GetAccTime();
			IsAttack = true;
			CurrentCollision = AttackCollision;
			DelayAttackTime = 0.1f;
			PrevPlayerState = EPlayerState::PState_Att2;
			break;
		case EPlayerState::PState_Att3:
			if (PrevPlayerState == EPlayerState::PState_Att3)
				return;
			GameServerDebug::Log(LOGTYPE::LOGTYPE_ERROR, "Attack3");

			AttTime = GetAccTime();
			IsAttack = true;
			CurrentCollision = AttackCollision;
			DelayAttackTime = 0.3f;
			PrevPlayerState = EPlayerState::PState_Att3;
			break;
		case EPlayerState::PState_Att4:
			if (PrevPlayerState == EPlayerState::PState_Att4)
				return;
			GameServerDebug::Log(LOGTYPE::LOGTYPE_ERROR, "Attack4");

			AttTime = GetAccTime();
			IsAttack = true;
			CurrentCollision = AttackCollision;
			DelayAttackTime = 0.3f;
			PrevPlayerState = EPlayerState::PState_Att4;
			break;
		case EPlayerState::PState_JumpAtt:
			if (PrevPlayerState == EPlayerState::PState_JumpAtt)
				return;
			GameServerDebug::Log(LOGTYPE::LOGTYPE_ERROR, "Jump");

			AttTime = GetAccTime();
			IsAttack = true;
			CurrentCollision = AttackCollision;
			DelayAttackTime = 0.3f;
			PrevPlayerState = EPlayerState::PState_JumpAtt;
			break;
		case EPlayerState::PState_SlamAtt:
			if (PrevPlayerState == EPlayerState::PState_SlamAtt)
				return;
			GameServerDebug::Log(LOGTYPE::LOGTYPE_ERROR, "SLAM");
			AttTime = GetAccTime();
			IsAttack = true;
			CurrentCollision = AttackCollision;
			DelayAttackTime = 0.7f;
			CurrentCollision = SlamCollision;
			PrevPlayerState = EPlayerState::PState_SlamAtt;

			break;
		case EPlayerState::PState_Idle:
			PrevPlayerState = EPlayerState::PState_Idle;
			break;
		case EPlayerState::PState_DoubleJump:
			PrevPlayerState = EPlayerState::PState_DoubleJump;
			break;
		case EPlayerState::PState_Jump:
			PrevPlayerState = EPlayerState::PState_Jump;
			break;
		case EPlayerState::PState_Move:
			PrevPlayerState = EPlayerState::PState_Move;
			break;
		}
	}
}