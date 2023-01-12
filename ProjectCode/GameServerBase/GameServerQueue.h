#pragma once
#include "GameServerNameBase.h"
#include "GameServerIocp.h"
#include "GameServerObjectPool.h"

// 용도 : 
// 분류 :
// 첨언 : 한번 iocp를 감싸서 기본규칙을 정의한 Queue

enum class IocpWaitReturnType
{
	RETURN_ERROR,
	RETURN_TIMEOUT,
	RETURN_OK,
};

class GameServerQueue : public GameServerNameBase
{

private:
	static void QueueFunction(std::shared_ptr<GameServerIocpWorker> _Work, GameServerQueue* _this, const std::string& _ThreadName);
public:
	enum class WORK_TYPE : char
	{
		Default, 
		Extension
	};

	enum class QUEUE_RETURN : char
	{
		OK,
		TIMEOUT,
		EMPTY,
		DESTROY,
	};


private: 
	struct PostJob : public std::enable_shared_from_this<PostJob>
	{
		std::function<void()> task_;
	};

	struct OverlappedJob : public std::enable_shared_from_this<PostJob>
	{
		std::function<void(BOOL _Result, DWORD _NumberOfBytes, LPOVERLAPPED)> task_;
	};


	mutable GameServerObjectFindPool<OverlappedJob> IocpOverlappedJobPool_;

	// enum의 byte크기를 제한할수가 있다.


	enum class WORKMESSAGE_TYPE : char
	{
		MSG_POST = -2, // 기본형 
		MSG_DESTROY = -1,
		// 0 이상이면
		// 서버메세지
	};


private:
	// IOCP_TYPE WorkType_;
	GameServerIocp Iocp;

public: // Default
	GameServerQueue();

	GameServerQueue(WORK_TYPE _Type, int threadCount, const std::string& _ThreadName = "", std::function<void()> _InitFunction = nullptr);
	~GameServerQueue();

	GameServerQueue(const GameServerQueue& _Other) = delete;
	GameServerQueue(GameServerQueue&& _Other) noexcept;

protected:
	GameServerQueue& operator=(const GameServerQueue& _Other) = delete;
	GameServerQueue& operator=(GameServerQueue&& _Other) = delete;

private:
	// 자기가 쓰레드 만들어서 처리하는 것들이 다 여기죠?
	void Run(std::shared_ptr<GameServerIocpWorker> _Work);
	GameServerQueue::QUEUE_RETURN WorkThread(std::shared_ptr<GameServerIocpWorker> _Work);
	GameServerQueue::QUEUE_RETURN WorkDefault(std::shared_ptr<GameServerIocpWorker> _Work); // 한번에 하나씩.
	GameServerQueue::QUEUE_RETURN WorkExtension(std::shared_ptr<GameServerIocpWorker> _Work); // 한번에 여러개
	std::function<GameServerQueue::QUEUE_RETURN(std::shared_ptr<GameServerIocpWorker> _Work)> WorkFunction;

private:
	void SetWorkType(WORK_TYPE _WorkType);

public: // Member Function
	void EnQueue(const std::function<void()>& _callback);
	void Destroy();
	bool NetWorkBind(SOCKET _Socket, std::function<void(BOOL, DWORD, LPOVERLAPPED)> _callback) const;
	void Initialize(WORK_TYPE _Type,
		int threadCount,
		const std::string& _ThreadName,
		std::function<void()> _InitFunction);

	void Initialize(int threadCount);

private:
	std::function<GameServerQueue::QUEUE_RETURN(DWORD)> ExecuteWorkFunction;

public:
	// 유저들이 이걸 사용할때는 잘 알아보고 사용하게 해야겠죠?
	void SetExecuteWorkType(WORK_TYPE _WorkType);
	GameServerQueue::QUEUE_RETURN Execute(DWORD _Time);

private:
	GameServerQueue::QUEUE_RETURN ExecuteOriginal(DWORD _Time);

	GameServerQueue::QUEUE_RETURN ExecuteEx(DWORD _Time);

};



