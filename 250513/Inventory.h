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
	void RunItem(int ItemIndex);

public:
	void Run();

private:
	static CInventory* mInst;

public:
	static CInventory* GetInst();
	static void DestroyInst();
};

