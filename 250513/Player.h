#pragma once

#include "GameInfo.h"

enum class EPlayerJob : unsigned char
{
	None,
	Knight,
	Archer,
	Magicion,
	End
};

namespace EEquip
{
	enum Type
	{
		None = -1,
		Weapon,
		Armor,
		End
	};
}

class CItem;
class CPlayer
{
public:
	CPlayer();
	~CPlayer();

private:
	char	mName[32] = {};
	EPlayerJob	mJob = EPlayerJob::None;
	int		mAttack = 0;
	int		mDefense = 0;
	int		mHP = 0;
	int		mHPMax = 0;
	int		mMP = 0;
	int		mMPMax = 0;
	int		mLevel = 1;
	int		mExp = 0;
	int		mGold = 10000;

	CItem* mEquipItem[EEquip::End] = {};

public:
	CItem* GetEquipItem(EEquip::Type EquipType)
	{
		return mEquipItem[EquipType];
	}

	CItem* Equip(EEquip::Type EquipType, CItem* Item)
	{
		CItem* EquipItem = mEquipItem[EquipType];
		mEquipItem[EquipType] = Item;
		return EquipItem;
	}

	int GetAttack()	const
	{
		return mAttack;
	}

	int GetDefense()	const
	{
		return mDefense;
	}

	// 리턴타입이 bool인 이유는 죽었는지 살았는지 반환하기 위해서이다.
	bool Damage(int Dmg)
	{
		mHP -= Dmg;

		return mHP > 0;
	}

	int GetExp()	const
	{
		return mExp;
	}

	int GetGold()	const
	{
		return mGold;
	}

	void AddExp(int Exp)
	{
		mExp += Exp;
	}

	void AddGold(int Gold)
	{
		mGold += Gold;
	}

	void Restore()
	{
		mHP = mHPMax;
		mMP = mMPMax;
	}

public:
	bool Init();
	bool Init(const char* Name, EPlayerJob Job, 
		const FPlayerEditorInfo& JobInfo);
	void Output();
	void LevelUp();
};

