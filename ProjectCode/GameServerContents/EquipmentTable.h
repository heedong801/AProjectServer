#pragma once
#include <GameServerNet\DBQuery.h>
#include <vector>
#include "InventoryTable.h"
// 용도 : 
// 분류 :
// 첨언 : 

class EquipRow : public std::enable_shared_from_this<EquipRow>
{
public:
	int			ItemIdx;
	//int			HeadBand;
	//int			Head;
	//int			Eye;
	//int			Neck;
	//int			Face;
	//int			Shoulder;
	//int			Armor;
	//int			Chest;
	//int			Body;
	//int			MainHand;
	//int			MainWrist;
	//int			Belt;
	//int			OffWrist;
	//int			OffHand;
	//int			RightHand;
	//int			Trousers;
	//int			LeftHand;
	//int			RightRing;
	//int			Feet;
	//int			LeftRing;
	std::vector<int> ItemPartVec;


public:
	EquipRow()
	{
	}

	/*EquipRow(
		int			_ItemIdx,
	int			_HeadBand,
	int			_Head,
	int			_Eye,
	int			_Neck,
	int			_Face,
	int			_Shoulder,
	int			_Armor,
	int			_Chest,
	int			_Body,
	int			_MainHand,
	int			_MainWrist,
	int			_Belt,
	int			_OffWrist,
	int			_OffHand,
	int			_RightHand,
	int			_Trousers,
	int			_LeftHand,
	int			_RightRing,
	int			_Feet,
	int			_LeftRing)
		:ItemIdx(_ItemIdx),
		 HeadBand(_HeadBand),
		Head(_Head),
		Eye(_Eye),
		Neck(_Neck),
		Face(_Face),
		Shoulder(_Shoulder),
		Armor(_Armor),
		Chest(_Chest),
		Body(_Body),
		MainHand(_MainHand),
		MainWrist(_MainWrist),
		Belt(_Belt),
		OffWrist(_OffWrist),
		OffHand(_OffHand),
		RightHand(_RightHand),
		Trousers(_Trousers),
		LeftHand(_LeftHand),
		RightRing(_RightRing),
		Feet(_Feet),
		LeftRing(_LeftRing)

	{
	}*/


};

class EquipmentTable_InsertCharacter : public DBQuery
{
public:
	int CharacterIdx;
public:
	EquipmentTable_InsertCharacter(int _CharacterIdx);
	bool DoQuery() override;
};

class EquipmentTable_UpdateNeckPart : public DBQuery
{
public:
	int CharacterIdx;
	int CurrentItemIdx;
	int ChangeItemIdx;

public:
	EquipmentTable_UpdateNeckPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx);

	bool DoQuery() override;
};

class EquipmentTable_UpdateArmorPart : public DBQuery
{
public:
	int CharacterIdx;
	int CurrentItemIdx;
	int ChangeItemIdx;
public:
	EquipmentTable_UpdateArmorPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx);


	bool DoQuery() override;
};

class EquipmentTable_UpdateMainHandPart : public DBQuery
{
public:
	int CharacterIdx;
	int CurrentItemIdx;
	int ChangeItemIdx;
public:
	EquipmentTable_UpdateMainHandPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx);


	bool DoQuery() override;
};

class EquipmentTable_SelectAllPart : public DBQuery
{
public:
	int CharacterIdx;
	std::vector<int> Data;
public:
	EquipmentTable_SelectAllPart(int _CharacterIdx);

	bool DoQuery() override;
};

