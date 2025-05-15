#pragma once

#include "GameInfo.h"

class CMonster
{
public:
	CMonster();
	CMonster(const CMonster& Monster);
	~CMonster();

private:
	char	mName[32] = {};
	int		mAttack = 0;
	int		mDefense = 0;
	int		mHP = 0;
	int		mHPMax = 0;
	int		mMP = 0;
	int		mMPMax = 0;
	int		mLevel = 1;

	// 아래 정보는 플레이어가 몬스터를 잡았을 때 획득할 수 있는 경험치와
	// 돈이다.
	int		mExp = 0;
	int		mGold = 0;

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

public:
	bool Init(const FMonsterEditorInfo& Info);
	void Output();
	// 자기 자신을 복제한 새로운 객체를 만들어준다.
	CMonster* Clone();
};

