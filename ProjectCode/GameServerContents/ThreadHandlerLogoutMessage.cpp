#include "PreCompile.h"
#include "ThreadHandlerLogoutMessage.h"
#include <GameServerCore\DBQueue.h>
#include "UserTable.h"

//#include "DBQueue.h"
//#include "NetQueue.h"

ThreadHandlerLogoutMessage::ThreadHandlerLogoutMessage()
{

}

ThreadHandlerLogoutMessage::~ThreadHandlerLogoutMessage()
{

}

void ThreadHandlerLogoutMessage::Start()
{
	if (nullptr == Session_)
	{
		GameServerDebug::LogError("Logout TCPSession Error");
	}

	DBWork(&ThreadHandlerLogoutMessage::DBCheck);
}

void ThreadHandlerLogoutMessage::DBCheck()
{
	UserTable_UpdateUserInfo UpdateQuery = UserTable_UpdateUserInfo(Message_->ID, 0);

	if (true == UpdateQuery.DoQuery())
	{
		GameServerDebug::LogInfo("UserTable_UpdateUserInfo Success Send");
	}
}