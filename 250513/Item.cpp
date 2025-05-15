#include "Item.h"

CItem::CItem()
{
}

CItem::CItem(const CItem& Item)
{
    *this = Item;
}

CItem::~CItem()
{
}

bool CItem::Init(FILE* File)
{
    fread(mName, sizeof(char), 32, File);
    fread(&mItemType, sizeof(EItemType::Type), 1, File);
    fread(&mOption, sizeof(int), 1, File);
    fread(&mPrice, sizeof(int), 1, File);
    fread(&mSell, sizeof(int), 1, File);
    fread(&mUpgrade, sizeof(int), 1, File);

    return true;
}

void CItem::Output()
{
	printf("이름 : %s", mName);

	if (mUpgrade > 0)
		printf(" + %d", mUpgrade);

	printf("\t종류 : ");

	switch (mItemType)
	{
	case EItemType::Weapon:
		printf("무기\n");
		printf("공격력 : %d\n", mOption);
		break;
	case EItemType::Armor:
		printf("방어구\n");
		printf("방어력 : %d\n", mOption);
		break;
	}

	printf("상점구매가격 : %d\t상점판매가격 : %d\n",
		mPrice, mSell);
}

CItem* CItem::Clone()
{
    return new CItem(*this);
}
