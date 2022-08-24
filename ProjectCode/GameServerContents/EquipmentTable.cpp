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
EquipmentTable_UpdateMainHandPart::EquipmentTable_UpdateMainHandPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx)
	: DBQuery("UPDATE userver2.equipinfo SET mainhand = ? Where CharacterIdx = ?")
	, CharacterIdx(_CharacterIdx)
	, CurrentItemIdx(_CurrentItemIdx)
	, ChangeItemIdx(_ChangeItemIdx)
{
}

bool EquipmentTable_UpdateMainHandPart::DoQuery()
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
EquipmentTable_UpdateArmorPart::EquipmentTable_UpdateArmorPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx)
	: DBQuery("UPDATE userver2.equipinfo SET armor = ? Where CharacterIdx = ?")
	, CharacterIdx(_CharacterIdx)
	, CurrentItemIdx(_CurrentItemIdx)
	, ChangeItemIdx(_ChangeItemIdx)
{
}

bool EquipmentTable_UpdateArmorPart::DoQuery()
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
EquipmentTable_UpdateOffHandPart::EquipmentTable_UpdateOffHandPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx)
	: DBQuery("UPDATE userver2.equipinfo SET offhand = ? Where CharacterIdx = ?")
	, CharacterIdx(_CharacterIdx)
	, CurrentItemIdx(_CurrentItemIdx)
	, ChangeItemIdx(_ChangeItemIdx)
{
}

bool EquipmentTable_UpdateOffHandPart::DoQuery()
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
EquipmentTable_UpdateMainWristPart::EquipmentTable_UpdateMainWristPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx)
	: DBQuery("UPDATE userver2.equipinfo SET mainwrist = ? Where CharacterIdx = ?")
	, CharacterIdx(_CharacterIdx)
	, CurrentItemIdx(_CurrentItemIdx)
	, ChangeItemIdx(_ChangeItemIdx)
{
}

bool EquipmentTable_UpdateMainWristPart::DoQuery()
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
EquipmentTable_UpdateLeftHandPart::EquipmentTable_UpdateLeftHandPart(int _CharacterIdx, int _CurrentItemIdx, int _ChangeItemIdx)
	: DBQuery("UPDATE userver2.equipinfo SET lefthand = ? Where CharacterIdx = ?")
	, CharacterIdx(_CharacterIdx)
	, CurrentItemIdx(_CurrentItemIdx)
	, ChangeItemIdx(_ChangeItemIdx)
{
}

bool EquipmentTable_UpdateLeftHandPart::DoQuery()
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
EquipmentTable_SelectAllPart::EquipmentTable_SelectAllPart(int _CharacterIdx)
	: DBQuery("SELECT * FROM userver2.equipinfo WHERE CharacterIdx = ? ")
	, CharacterIdx(_CharacterIdx)
{

}

bool EquipmentTable_SelectAllPart::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(CharacterIdx);

	std::unique_ptr<DBStmtResult> Result(Stmt->Execute());

	uint64_t Row = Stmt->AffectedRows();

	if (0 >= Row)
	{
		return false;
	}

	Result->Next();
	Data.clear();
	Data.resize(21);

	/*RowData =	std::make_shared<EquipRow>(EquipRow(
			Result->GetInt(0),
			Result->GetInt(1),
			Result->GetInt(2),
			Result->GetInt(3),
			Result->GetInt(4),
			Result->GetInt(5),
			Result->GetInt(6),
			Result->GetInt(7),
			Result->GetInt(8),
			Result->GetInt(9),
			Result->GetInt(10),
			Result->GetInt(11),
			Result->GetInt(12),
			Result->GetInt(13),
			Result->GetInt(14),
			Result->GetInt(15),
			Result->GetInt(16),
			Result->GetInt(17),
			Result->GetInt(18),
			Result->GetInt(19),
			Result->GetInt(20)
		));*/
	for (int i = 0; i < 21; i++)
	{
		Data[i] = Result->GetInt(i);
	}


	return true;
}



