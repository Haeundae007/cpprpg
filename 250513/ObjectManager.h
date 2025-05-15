#pragma once

#include "GameInfo.h"
#include "Array.h"
#include "Store.h"

class CMonster;
class CPlayer;
class CItem;
class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();

private:
	CPlayer* mPlayer = nullptr;
	int* mExpTable = nullptr;
	CMonster* mOriginMonster[(int)EMapMenu::MapCount];
	CArray<CItem*>	mOriginItemArray;

	//class CPlayer*

public:
	CPlayer* GetPlayer()	const
	{
		return mPlayer;
	}

	int GetLevelExp(int Level)	const
	{
		return mExpTable[Level - 1];
	}

public:
	bool Init();
	CMonster* CloneMonster(EMapMenu MapType);
	void AddStoreItem(CArray<CItem*>& ItemList, 
		EStoreType::Type StoreType);

private:
	bool LoadPlayer();
	bool LoadLevelExp();
	bool LoadMonster();
	bool LoadItem();

private:
	static CObjectManager* mInst;

public:
	static CObjectManager* GetInst();
	static void DestroyInst();
};

