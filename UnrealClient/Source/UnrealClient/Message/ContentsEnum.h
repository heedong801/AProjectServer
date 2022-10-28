#pragma once

enum class EGameServerCode
{
	OK,
	FAIL,
	AlreadyPlay,
	DuplicateID,
	LoginError,
};


enum class EGameObjectType
{
	Player,
	Monster,
	Item,
	Potal,
	MAX,
};

enum class EPlayerState
{
	NONE,
	PState_Idle,
	PState_Move,
	PState_Att1,
	PState_Att2,
	PState_Att3,
	PState_Att4,
	PState_Death,
	PState_Jump,
	PState_JumpAtt,
	PState_DoubleJump,
	PState_SlamAtt,
	MAX,
};



enum class EMonsterState
{
	NONE,
	MState_Idle,
	MState_Trace,
	MState_Att,
	MState_Death,
	MAX,
};


enum class ESectionType
{
	NONE,
	NONEFIGHT,
	FIGHTZONE1,
	FIGHTZONE2,
	FIGHTZONE3,
	FIGHTZONE4,
	MAX,
};

enum class EChatMessageType
{
	NONE,
	ALL,
	ONEPLAYER,
	INSECTION,
	MAX,
};