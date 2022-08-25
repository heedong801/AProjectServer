#pragma once
#include <GameServerNet\DBQuery.h>
#include "ContentsStructure.h"
class CharacterRow : public std::enable_shared_from_this<CharacterRow>
{
public:
	union {
		struct 
		{
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
		};
		FCharacterInfo Info;
	};


public:
	CharacterRow(
		int _Index,
		std::string _NickName,
		int _UserIndex,
		int _Att,
		int _Armor,
		int _HpMax,
		int _MpMax,
		int _Hp,
		int _Mp,
		int _HpRecovery,
		int _MpRecovery,
		int _CriticalPercent,
		int _CriticalDamage,
		int _LastSectionID,
		float _SectionX,
		float _SectionY,
		float _SectionZ
	) : Index(_Index),
		NickName(_NickName),
		UserIndex(_UserIndex),
		Att(_Att),
		Armor(_Armor),
		HpMax(_HpMax),
		MpMax(_MpMax),
		Hp(_Hp),
		Mp(_Mp),
		HpRecovery(_HpRecovery),
		MpRecovery(_MpRecovery),
		CriticalPercent(_CriticalPercent),
		CriticalDamage(_CriticalDamage),
		LastSectionID(_LastSectionID),
		SectionX(_SectionX),
		SectionY(_SectionY),
		SectionZ(_SectionZ)
	{

	}

	CharacterRow(
		const CharacterRow& _Data
	) : Index(_Data.Index),
		NickName(_Data.NickName),
		UserIndex(_Data.UserIndex),
		Att(_Data.Att),
		Armor(_Data.Armor),
		HpMax(_Data.HpMax),
		MpMax(_Data.MpMax),
		Hp(_Data.Hp),
		Mp(_Data.Mp),
		HpRecovery(_Data.HpRecovery),
		MpRecovery(_Data.MpRecovery),
		CriticalPercent(_Data.CriticalPercent),
		CriticalDamage(_Data.CriticalDamage),
		LastSectionID(_Data.LastSectionID),
		SectionX(_Data.SectionX),
		SectionY(_Data.SectionY),
		SectionZ(_Data.SectionZ)
	{

	}



	CharacterRow(
		const FCharacterInfo& _Data
	) : Info(_Data)
	{

	}

	~CharacterRow() {
	}
};



class CharacterTable_SelectNickName : public DBQuery
{
public:
	std::string NickName;
	std::shared_ptr<CharacterRow> RowData;

	
	FCharacterInfo ConvertInfoCharacter() 
	{
		FCharacterInfo Info;

		Info.Index = RowData->Index;
		Info.NickName = RowData->NickName;
		Info.UserIndex = RowData->UserIndex;
		Info.Att = RowData->Att;
		Info.Armor = RowData->Armor;
		Info.HpMax = RowData->HpMax;
		Info.MpMax = RowData->MpMax;
		Info.Hp = RowData->Hp;
		Info.Mp = RowData->Mp;
		Info.HpRecovery = RowData->HpRecovery;
		Info.MpRecovery = RowData->MpRecovery;
		Info.CriticalPercent = RowData->CriticalPercent;
		Info.CriticalDamage = RowData->CriticalDamage;
		Info.LastSectionID = RowData->LastSectionID;
		Info.SectionX = RowData->SectionX;
		Info.SectionY = RowData->SectionY;
		Info.SectionZ = RowData->SectionZ;
	}
	

public:
	CharacterTable_SelectNickName(std::string _NickName);
	bool DoQuery() override;
};


class CharacterTable_SelectUserCharacters : public DBQuery
{
public:
	std::vector<std::shared_ptr<CharacterRow>> RowDatas;
	int UserIndex_;

public:
	CharacterTable_SelectUserCharacters(int _Idx);

	bool DoQuery() override;
};



class CharacterTable_CreateCharacter : public DBQuery
{
public:
	std::string NickName;
	int Id_;

public:
	CharacterTable_CreateCharacter(std::string _NickName, int _Id);
	bool DoQuery() override;
};

class CharacterTable_UpdateCharacter : public DBQuery
{
public:
	int			CharacterId;
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
public:
	CharacterTable_UpdateCharacter(int _CharacterId, int _Att, int _Armor, int _HpMax, int _MpMax, int _Hp, int _Mp, int _HpRecovery, int _MpRecovery, int _CriticalPercent, int _CriticalDamage);
	bool DoQuery() override;
};

