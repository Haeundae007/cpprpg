#pragma once

#include <iostream>
#include <assert.h>
#include <time.h>

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }

enum class EMapMenu : unsigned char
{
	None,
	Easy,
	Normal,
	Hard,
	Back,
	End,
	MapCount = Back - 1
};

struct FPlayerEditorInfo
{
	int		Attack = 0;
	int		Defense = 0;
	int		HP = 0;
	int		MP = 0;
};

struct FMonsterEditorInfo
{
	char	Name[32] = {};
	int		Attack = 0;
	int		Defense = 0;
	int		HP = 0;
	int		MP = 0;
	int		Level = 1;
	int		Exp = 0;
	int		Gold = 0;
};
