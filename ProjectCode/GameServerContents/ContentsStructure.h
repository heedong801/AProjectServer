#pragma once
#include <GameServerBase\GameServerSerializer.h>

struct FCharacterInfo
{
public:
	int			Index;
	std::string NickName;
	int			UserIndex;
	int			Att;
	int			Armor;
	int			HpMax;
	int			MpMax;
	int			Hp;
	int			Mp;
	int			HpRecovery;
	int			MpRecovery;
	int			CriticalPercent;
	int			CriticalDamage;
	int			LastSectionID;
	float		SectionX;
	float		SectionY;
	float		SectionZ;
public:
	int GetDataSize() 
	{
		return (4 * 16) + 4 + static_cast<int>(NickName.size());
	}

	void Serialize(GameServerSerializer& _Ser) 
	{
		_Ser << Index;
		_Ser << NickName;
		_Ser << UserIndex;
		_Ser << Att;
		_Ser << Armor;
		_Ser << HpMax;
		_Ser << MpMax;
		_Ser << Hp;
		_Ser << Mp;
		_Ser << HpRecovery;
		_Ser << MpRecovery;
		_Ser << CriticalPercent;
		_Ser << CriticalDamage;
		_Ser << LastSectionID;
		_Ser << SectionX;
		_Ser << SectionY;
		_Ser << SectionZ;
	}

	void DeSerialize(GameServerSerializer& _Ser)
	{
		_Ser >> Index;
		_Ser >> NickName;
		_Ser >> UserIndex;
		_Ser >> Att;
		_Ser >> Armor;
		_Ser >> HpMax;
		_Ser >> MpMax;
		_Ser >> Hp;
		_Ser >> Mp;
		_Ser >> HpRecovery;
		_Ser >> MpRecovery;
		_Ser >> CriticalPercent;
		_Ser >> CriticalDamage;
		_Ser >> LastSectionID;
		_Ser >> SectionX;
		_Ser >> SectionY;
		_Ser >> SectionZ;
	}


	FCharacterInfo() {
	}
	~FCharacterInfo() {
	}
};

struct FPlayerUpdateData
{
	FVector4 Dir;
	FVector4 Pos;
	FVector4 Rot;
	uint64_t ObjectIndex;
	uint64_t ThreadIndex;
	uint64_t SectionIndex;
	int State;

	template<typename EnumType>
	EnumType GetState()
	{
		return static_cast<EnumType>(State);
	}

	template<typename EnumType>
	void SetState(EnumType _Type)
	{
		State = static_cast<int>(_Type);
	}


	int GetDataSize()
	{
		return sizeof(FPlayerUpdateData);
	}

	void Serialize(GameServerSerializer& _Ser)
	{
		_Ser << ObjectIndex;
		_Ser << ThreadIndex;
		_Ser << SectionIndex;
		_Ser << Dir;
		_Ser << Pos;
		_Ser << Rot;
		_Ser << State;
	}

	void DeSerialize(GameServerSerializer& _Ser)
	{
		_Ser >> ObjectIndex;
		_Ser >> ThreadIndex;
		_Ser >> SectionIndex;
		_Ser >> Dir;
		_Ser >> Pos;
		_Ser >> Rot;
		_Ser >> State;
	}


	FPlayerUpdateData() {
	}
	~FPlayerUpdateData() {
	}
};


struct FMonsterUpdateData
{
	FVector4 Dir;
	FVector4 Pos;
	FVector4 Rot;
	uint64_t ObjectIndex;
	uint64_t ThreadIndex;
	uint64_t SectionIndex;
	float DeltaTime;
	int State;

	template<typename EnumType>
	EnumType GetState()
	{
		return static_cast<EnumType>(State);
	}

	template<typename EnumType>
	void SetState(EnumType _Type)
	{
		State = static_cast<int>(_Type);
	}


	int GetDataSize()
	{
		return sizeof(FMonsterUpdateData);
	}

	void Serialize(GameServerSerializer& _Ser)
	{
		_Ser << ObjectIndex;
		_Ser << ThreadIndex;
		_Ser << SectionIndex;
		_Ser << Dir;
		_Ser << Pos;
		_Ser << Rot;
		_Ser << State;
	}

	void DeSerialize(GameServerSerializer& _Ser)
	{
		_Ser >> ObjectIndex;
		_Ser >> ThreadIndex;
		_Ser >> SectionIndex;
		_Ser >> Dir;
		_Ser >> Pos;
		_Ser >> Rot;
		_Ser >> State;
	}


	FMonsterUpdateData() {
	}
	~FMonsterUpdateData() {
	}
};

struct FPlayerItemData
{
	uint64_t ObjectIndex;
	uint64_t ItemIndex;
	std::string ItemName;
	int ItemType;
	int ItemTier;
	int ItemPart;

	int GetDataSize()
	{
		return ( 8 * 2 ) + (4 * 3) + 4 + static_cast<int>(ItemName.size());
	}

	void Serialize(GameServerSerializer& _Ser)
	{
		_Ser << ObjectIndex;
		_Ser << ItemIndex;
		_Ser << ItemName;
		_Ser << ItemType;
		_Ser << ItemTier;
		_Ser << ItemPart;
	}

	void DeSerialize(GameServerSerializer& _Ser)
	{
		_Ser >> ObjectIndex;
		_Ser >> ItemIndex;
		_Ser >> ItemName;
		_Ser >> ItemType;
		_Ser >> ItemTier;
		_Ser >> ItemPart;
	}

	FPlayerItemData() {
	}
	~FPlayerItemData() {
	}
};