#pragma once
#include <GameServerCore\ThreadHandlerBase.h>
#include "ClientToServer.h"
#include "ServerToClient.h"
// ���� :

class ThreadHandlerGetInventoryMessage final
	: public ThreadHandlerBase<GetInventoryMessage>
{
	// ó���� ���
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
	// �� �޼����� ó���ϴ� �ܰ�
	void DBCheck();

	void ResultSend();

protected:

private:
	// �� �޼����� ó�� �޾����� �����ϴ� �Լ�

};

