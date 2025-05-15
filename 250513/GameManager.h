#pragma once

#include "GameInfo.h"

class CGameManager
{
private:
	CGameManager();
	~CGameManager();

public:
	bool Init();
	void Run();


private:
	static CGameManager* mInst;

public:
	static CGameManager* GetInst();
	static void DestroyInst();
};

