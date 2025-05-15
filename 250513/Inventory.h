#pragma once

#include "GameInfo.h"
#include "Array.h"

class CItem;
class CInventory
{
private:
	CInventory();
	~CInventory();

private:
	CArray<CItem*>	mItemList;
	int				mItemMaxCount = 10;
	int				mItemCount = 0;
	float			mUpgradeRate[ITEM_UPGRADE_MAX] =
	{
		100.f, 100.f, 100.f, 90.f, 85.f, 80.f, 75.f, 70.f, 65.f, 60.f,
		20.f, 15.f, 10.f, 5.f, 1.f, 0.5f, 0.3f, 0.1f, 0.07f, 0.05f
	};

public:
	int GetItemMaxCount()	const
	{
		return mItemMaxCount;
	}

	bool IsFull()	const
	{
		return mItemMaxCount == mItemCount;
	}

public:
	void AddItem(CItem* Item);

public:
	bool Init();

private:
	void Equip(int ItemIndex);
	void Upgrade(int ItemIndex);
	void Sell(int ItemIndex);
	void RunItem(int ItemIndex);

public:
	void Run();

private:
	static CInventory* mInst;

public:
	static CInventory* GetInst();
	static void DestroyInst();
};

