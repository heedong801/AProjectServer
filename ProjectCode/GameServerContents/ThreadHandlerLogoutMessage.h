#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>
#include <GameServerCore\ThreadHandlerBase.h>
#include "ClientToServer.h"



// 그 세션도 여기서 받는다.
class ThreadHandlerLogoutMessage final
	: public ThreadHandlerBase<LogoutMessage>
{
private: // Member Var

public: // Default
	ThreadHandlerLogoutMessage();
	~ThreadHandlerLogoutMessage();
	ThreadHandlerLogoutMessage(const ThreadHandlerLogoutMessage& _Other) = delete;
	ThreadHandlerLogoutMessage(ThreadHandlerLogoutMessage&& _Other) noexcept = delete;
	ThreadHandlerLogoutMessage& operator=(ThreadHandlerLogoutMessage&& _Other) = delete;
	ThreadHandlerLogoutMessage& operator=(const ThreadHandlerLogoutMessage& _Other) = delete;

	void Start() override;
	void DBCheck();

private:

protected:

};