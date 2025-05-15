
#include "GameManager.h"

int main()
{
	// CGameManager::GetInst()를 하면 객체를 생성하고 -> 를 이용해 생성한 객체의
	// 멤버에 접근할 수 있다.
	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();

	CGameManager::DestroyInst();

	return 0;
}
