#include "PreCompile.h"
#include "OptionTable.h"

//////////////////////////////////////////////////////////////////// 

OptionTable_SelectItemOption::OptionTable_SelectItemOption(int _ItemIdx)
	: DBQuery("SELECT * FROM userver2.optioninfo WHERE ItemIdx = ?")
	, ItemIdx(_ItemIdx)
{
}

bool OptionTable_SelectItemOption::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(ItemIdx);

	std::unique_ptr<DBStmtResult> Result(Stmt->Execute());

	uint64_t Row = Result->AffectedRows();

	if (1 != Result->AffectedRows())
	{
		return false;
	}

	if (false == Result->Next())
	{
		return false;
	}

	RowData = std::make_shared<OptionRow>(Result->GetInt(0), Result->GetInt(1), Result->GetInt(2),
		Result->GetInt(3), Result->GetInt(4), Result->GetInt(5),
		Result->GetInt(6), Result->GetInt(7), Result->GetInt(8),
		Result->GetInt(9), Result->GetInt(10));
	return true;
}