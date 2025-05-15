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

	//FItem* EquipItem[EEquip::End] = {};

public:
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

