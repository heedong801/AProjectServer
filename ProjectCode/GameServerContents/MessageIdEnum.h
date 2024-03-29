#pragma once

enum class MessageId 
{
	Login,
	CreateCharacter,
	SelectCharacter,
	ClientToReady,
	LevelMoveReply,
	RankRequest,
	GetInventory,
	EquipItem,
	Logout,
	LoginResult,
	CharacterCreateResult,
	CharacterSelectResult,
	LevelMove,
	UDPReadyOK,
	SectionInsertResult,
	ServerDestroy,
	PlayerDestroy,
	ObjectDestroy,
	CharacterList,
	PlayersUpdate,
	MonsterUpdate,
	UserRankWindowData,
	GetItem,
	GetInventoryResult,
	GetEquipmentResult,
	SetCharacterStat,
	Chat,
	PlayerUpdate,
	MAX
};