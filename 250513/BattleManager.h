#pragma once

#include "GameInfo.h"

// 전방선언 : 이 클래스가 어딘가에 있다고 가정하고 포인터 변수를 사용할 수 있게
// 만들어준다. 실제 사용 부분에서는 include를 해주어야 한다.
class CBattle;
class CBattleManager
{
private:
	CBattleManager();
	~CBattleManager();

private:
	CBattle* mBattle = nullptr;

public:
	bool Init();
	void Run();

private:
	static CBattleManager* mInst;

public:
	static CBattleManager* GetInst();
	static void DestroyInst();
};

