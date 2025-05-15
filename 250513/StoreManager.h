#pragma once

#include "GameInfo.h"

class CStoreManager
{
private:
	CStoreManager();
	~CStoreManager();

public:
	bool Init();
	void Run();

private:
	static CStoreManager* mInst;

public:
	static CStoreManager* GetInst();
	static void DestroyInst();
};

