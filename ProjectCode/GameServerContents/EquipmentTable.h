#pragma once
#include <GameServerNet\DBQuery.h>
#include <vector>
#include "InventoryTable.h"

class EquipRow : public std::enable_shared_from_this<EquipRow>
{
public:
	int			ItemIdx;
	
	std::vector<int> ItemPartVec;


public:
	EquipRow()
	{
	}

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

class EquipmentTable_UpdateOffHandPart : public DBQuery
{
public:
	int CharacterIdx;
	int CurrentItemIdx;
	int ChangeItemIdx;
public:
	EquipmentTable_UpdateOffHandPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx);


	bool DoQuery() override;
};

class EquipmentTable_UpdateMainWristPart : public DBQuery
{
public:
	int CharacterIdx;
	int CurrentItemIdx;
	int ChangeItemIdx;
public:
	EquipmentTable_UpdateMainWristPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx);


	bool DoQuery() override;

};

class EquipmentTable_UpdateLeftHandPart : public DBQuery
{
public:
	int CharacterIdx;
	int CurrentItemIdx;
	int ChangeItemIdx;
public:
	EquipmentTable_UpdateLeftHandPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx);


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

