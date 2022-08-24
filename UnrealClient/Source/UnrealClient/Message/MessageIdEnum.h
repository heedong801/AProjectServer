#pragma once

enum class MessageId 
{
	Login,
	CreateCharacter,
	SelectCharacter,
	ClientToReady,
	UDPConnectResult,
	LevelMoveReply,
	RankRequest,
	GetInventory,
	EquipItem,
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
	Chat,
	PlayerUpdate,
	MAX
};