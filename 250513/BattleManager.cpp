#include "BattleManager.h"
#include "Battle.h"

CBattleManager* CBattleManager::mInst = nullptr;

CBattleManager::CBattleManager()
{
}

CBattleManager::~CBattleManager()
{
}

bool CBattleManager::Init()
{
	return true;
}

void CBattleManager::Run()
{
	while (true)
	{
		// 전투 메뉴를 보여주고 선택한다.
		system("cls");
		printf("1. 쉬움\n");
		printf("2. 보통\n");
		printf("3. 어려움\n");
		printf("4. 뒤로가기\n");
		printf("메뉴를 선택하세요 : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		switch ((EMapMenu)Input)
		{
		case EMapMenu::Easy:
		case EMapMenu::Normal:
		case EMapMenu::Hard:
			mBattle = new CBattle;

			mBattle->Init((EMapMenu)Input);

			mBattle->Run();

			SAFE_DELETE(mBattle);
			break;
		case EMapMenu::Back:
			return;
		}
	}
}

CBattleManager* CBattleManager::GetInst()
{
	if (!mInst)
		mInst = new CBattleManager;

	return mInst;
}

void CBattleManager::DestroyInst()
{
	SAFE_DELETE(mInst);
}
