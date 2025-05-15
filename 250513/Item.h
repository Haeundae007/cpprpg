#pragma once

#include "GameInfo.h"

namespace EItemType
{
	enum Type
	{
		None = -1,
		Weapon,
		Armor,
		End
	};
}

class CItem
{
public:
	CItem();
	CItem(const CItem& Item);
	~CItem();

private:
	char	mName[32] = {};
	EItemType::Type	mItemType = EItemType::Weapon;
	int		mOption = 0;
	int		mPrice = 0;
	int		mSell = 0;
	int		mUpgrade = 0;

public:
	const char* GetName()	const
	{
		return mName;
	}

	EItemType::Type GetItemType()	const
	{
		return mItemType;
	}

	int GetOption()	const
	{
		return mOption;
	}

	int GetPrice()	const
	{
		return mPrice;
	}

	int GetSell()	const
	{
		return mSell;
	}

	int GetUpgrade()	const
	{
		return mUpgrade;
	}

public:
	bool Init(FILE* File);
	void Output();
	CItem* Clone();
};

