#pragma once

#include "GameInfo.h"
#include "Array.h"

namespace EStoreType
{
	enum Type
	{
		None,
		Weapon,
		Armor,
		Back,
		End
	};
}

class CItem;
class CStore
{
public:
	CStore();
	~CStore();

private:
	CArray<CItem*>	mItemList;
	EStoreType::Type	mStoreType;

public:
	bool Init(EStoreType::Type StoreType);
	void Run();
};

