#pragma once
#include <GameServerCore\ThreadHandlerBase.h>
#include "ClientToServer.h"
#include "ServerToClient.h"
// 설명 :

class ThreadHandlerGetInventoryMessage final
	: public ThreadHandlerBase<GetInventoryMessage>
{
	// 처리한 결과
	GetInventoryResultMessage Result_;


public:
	// constrcuter destructer
	ThreadHandlerGetInventoryMessage();
	~ThreadHandlerGetInventoryMessage();

	// delete Function
	ThreadHandlerGetInventoryMessage(const ThreadHandlerGetInventoryMessage& _Other) = delete;
	ThreadHandlerGetInventoryMessage(ThreadHandlerGetInventoryMessage&& _Other) noexcept = delete;
	ThreadHandlerGetInventoryMessage& operator=(const ThreadHandlerGetInventoryMessage& _Other) = delete;
	ThreadHandlerGetInventoryMessage& operator=(ThreadHandlerGetInventoryMessage&& _Other) noexcept = delete;

	void Start() override;
	// 이 메세지를 처리하는 단계
	void DBCheck();

	void ResultSend();

protected:

private:
	// 이 메세지를 처음 받았을때 실행하는 함수

};

