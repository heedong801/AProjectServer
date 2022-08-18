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
	Chat,
	PlayerUpdate,
	MAX
};