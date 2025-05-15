#pragma once

#include "GameInfo.h"

enum class EBattleResult : unsigned char
{
	None,
	PlayerDeath,
	MonsterDeath
};

class CBattle
{
public:
	CBattle();
	~CBattle();

private:
	EMapMenu	mMap;

public:
	bool Init(EMapMenu Map);

private:
	EBattleResult Battle(class CPlayer* Player, class CMonster* Monster);

public:
	void Run();
};

