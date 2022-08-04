#pragma once
#include "../ThreadHandlerBase.h"

class ThreadHandlerGetItemMessage : public ThreadHandlerBase<GetItemMessage>
{
public:
	void Start();
};