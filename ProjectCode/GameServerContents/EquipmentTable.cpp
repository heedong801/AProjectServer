#include "PreCompile.h"
#include "EquipmentTable.h"


EquipmentTable_InsertCharacter::EquipmentTable_InsertCharacter(int _CharacterId)
	: DBQuery("INSERT INTO userver2.equipinfo (CharacterIdx) VALUES (?);")
	, CharacterIdx(_CharacterId)
{
}

bool EquipmentTable_InsertCharacter::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(CharacterIdx);
	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();

	if (0 == Row)
	{
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////
EquipmentTable_UpdateNeckPart::EquipmentTable_UpdateNeckPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx)
	: DBQuery("UPDATE userver2.equipinfo SET neck = ? Where CharacterIdx = ?")
	, CharacterIdx(_CharacterIdx)
	, CurrentItemIdx(_CurrentItemIdx)
	, ChangeItemIdx(_ChangeItemIdx)
{
}

bool EquipmentTable_UpdateNeckPart::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(ChangeItemIdx);
	Stmt->ParamBindInt(CharacterIdx);

	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();

	if (0 == Row)
	{
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////
EquipmentTable_UpdateMainHandPart::EquipmentTable_UpdateMainHandPart(int _CharacterIdx, int _ItemIdx)
	: DBQuery("UPDATE userver2.equipinfo SET neck = ? Where CharacterIdx = ?")
	, CharacterIdx(_CharacterIdx)
	, ItemIdx(_ItemIdx)
{
}

bool EquipmentTable_UpdateMainHandPart::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(ItemIdx);
	Stmt->ParamBindInt(CharacterIdx);

	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();

	if (0 == Row)
	{
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////
EquipmentTable_UpdateArmorPart::EquipmentTable_UpdateArmorPart(int _CharacterIdx, int _ItemIdx)
	: DBQuery("UPDATE userver2.equipinfo SET neck = ? Where CharacterIdx = ?")
	, CharacterIdx(_CharacterIdx)
	, ItemIdx(_ItemIdx)
{
}

bool EquipmentTable_UpdateArmorPart::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(ItemIdx);
	Stmt->ParamBindInt(CharacterIdx);

	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();

	if (0 == Row)
	{
		return false;
	}

	return true;
}