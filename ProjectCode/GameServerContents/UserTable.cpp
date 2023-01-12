#include "PreCompile.h"
#include "UserTable.h"
#include <GameServerBase\GameServerThread.h>


//////////////////////////////////////////////////////////////////// 

UserTable_SelectIDToUserInfo::UserTable_SelectIDToUserInfo(std::string _ID)
	: DBQuery("SELECT Idx, ID, PW, ConnectStatus FROM userver2.userinfo WHERE ID = ? LIMIT 1")
	, ID(_ID)
	, RowData(nullptr)
{
}

bool UserTable_SelectIDToUserInfo::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindString(ID);

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

	RowData = std::make_shared<UserRow>(Result->GetInt(0) , Result->GetString(1) , Result->GetString(2), Result->GetInt(3));
	return true;
}

//////////////////////////////////////////////////////////////////// 

UserTable_AllUserInfo::UserTable_AllUserInfo()
	: DBQuery("SELECT * FROM userver2.userinfo")
	
{
}

bool UserTable_AllUserInfo::DoQuery()
{
	// 이 방어를 위한 시맨틱을 만들어달라고 해야하는데.
	// 이 시맨틱은 이미 구조체로 제공됩니다.
	// 방어를 하겠다.
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);
	std::unique_ptr<DBStmtResult> Result(Stmt->Execute());

	uint64_t Row = Result->AffectedRows();
	RowDatas.reserve(Row);

	while (Result->Next())
	{
		RowDatas.push_back(std::make_shared<UserRow>(Result->GetInt(0), Result->GetString(1), Result->GetString(2), Result->GetInt(3)));
	}
	return true;
}

//////////////////////////////////////////////////////////////////// 

UserTable_InsertUserInfo::UserTable_InsertUserInfo(std::string _ID, std::string _PW)
	: DBQuery("INSERT INTO userver2.userinfo (ID, PW) VALUES (?, ?)")
	, ID(_ID)
	, PW(_PW)
{
}

bool UserTable_InsertUserInfo::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindString(ID);
	Stmt->ParamBindString(PW);

	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();
	uint64_t Id = Stmt->InsertId();

	if (-1 == Row)
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////// 

UserTable_UpdateUserInfo::UserTable_UpdateUserInfo(std::string _ID, int _ConnectStatus)
	: DBQuery("Update userver2.userinfo SET ConnectStatus = ? Where ID = ?")
	, ID(_ID)
	, ConnectStatus(_ConnectStatus)
{
}

bool UserTable_UpdateUserInfo::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(ConnectStatus);
	Stmt->ParamBindString(ID);

	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();
	uint64_t Id = Stmt->InsertId();

	if (-1 == Row)
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////// 

UserTable_UpdateAll_ConnectStatus::UserTable_UpdateAll_ConnectStatus()
	: DBQuery("Update userver2.userinfo SET ConnectStatus = 0")
{
}

bool UserTable_UpdateAll_ConnectStatus::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();
	uint64_t Id = Stmt->InsertId();

	if (-1 == Row)
		return false;

	return true;
}
