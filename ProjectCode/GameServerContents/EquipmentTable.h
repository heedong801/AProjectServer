#pragma once
#include <GameServerNet\DBQuery.h>
#include <vector>
// 용도 : 
// 분류 :
// 첨언 : 

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
	int ItemIdx;
public:
	EquipmentTable_UpdateArmorPart(int _CharacterIdx, int _ItemIdx);

	bool DoQuery() override;
};

class EquipmentTable_UpdateMainHandPart : public DBQuery
{
public:
	int CharacterIdx;
	int ItemIdx;
public:
	EquipmentTable_UpdateMainHandPart(int _CharacterIdx, int _ItemIdx);

	bool DoQuery() override;
};

