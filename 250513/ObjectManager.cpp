#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"

CObjectManager* CObjectManager::mInst = nullptr;

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
    int Size = mOriginItemArray.size();

    for (int i = 0; i < Size; ++i)
    {
        SAFE_DELETE(mOriginItemArray[i]);
    }

    for (int i = 0; i < (int)EMapMenu::MapCount; ++i)
    {
        SAFE_DELETE(mOriginMonster[i]);
    }

    SAFE_DELETE_ARRAY(mExpTable);
    SAFE_DELETE(mPlayer);
}

bool CObjectManager::Init()
{
    if (!LoadPlayer())
        return false;

    if (!LoadLevelExp())
        return false;

    if (!LoadMonster())
        return false;

    if (!LoadItem())
        return false;

    return true;
}

CMonster* CObjectManager::CloneMonster(EMapMenu MapType)
{
    // Map은 1부터 시작이기 때문에 1을 빼서 0부터 시작하는 인덱스로 만들고
    // 해당 인덱스의 원본 몬스터를 복제한 새로운 몬스터를 만들어서 그 주소를
    // 반환해준다.
    return mOriginMonster[(int)MapType - 1]->Clone();
}

void CObjectManager::AddStoreItem(CArray<CItem*>& ItemList, 
    EStoreType::Type StoreType)
{
    EItemType::Type ItemType;

    switch (StoreType)
    {
    case EStoreType::Weapon:
        ItemType = EItemType::Weapon;
        break;
    case EStoreType::Armor:
        ItemType = EItemType::Armor;
        break;
    }

    int Size = mOriginItemArray.size();

    for (int i = 0; i < Size; ++i)
    {
        if (mOriginItemArray[i]->GetItemType() == ItemType)
        {
            ItemList.push_back(mOriginItemArray[i]);
        }
    }
}

bool CObjectManager::LoadPlayer()
{
    mPlayer = new CPlayer;

    if (!mPlayer->Init())
        return false;

    return true;
}

bool CObjectManager::LoadLevelExp()
{
    // 경험치 테이블을 읽어온다.
    FILE* File = nullptr;

    fopen_s(&File, "ExpTable.txt", "rt");

    if (!File)
        return false;

    char	Line[512] = {};

    fgets(Line, 512, File);

    int	TableCount = atoi(Line);

    mExpTable = new int[TableCount];

    fgets(Line, 512, File);

    // 문자열을 분리한다.
    char* Context = nullptr;
    char* TokResult = strtok_s(Line, ",", &Context);

    mExpTable[0] = atoi(TokResult);

    for (int i = 1; i < TableCount; ++i)
    {
        TokResult = strtok_s(nullptr, ",", &Context);

        mExpTable[i] = atoi(TokResult);
    }

    fclose(File);

    return true;
}

bool CObjectManager::LoadMonster()
{
    FMonsterEditorInfo  MonsterEditorInfo[(int)EMapMenu::MapCount];

    FILE* File = nullptr;

    fopen_s(&File, "MonsterInfo.mst", "rb");

    if (!File)
        return false;

    fread(MonsterEditorInfo, sizeof(FMonsterEditorInfo),
        (int)EMapMenu::MapCount, File);

    fclose(File);

    for (int i = 0; i < (int)EMapMenu::MapCount; ++i)
    {
        mOriginMonster[i] = new CMonster;

        mOriginMonster[i]->Init(MonsterEditorInfo[i]);
    }

    return true;
}

bool CObjectManager::LoadItem()
{
    FILE* File = nullptr;

    fopen_s(&File, "ItemList.itl", "rb");

    if (!File)
        return false;

    int ItemCount = 0;

    fread(&ItemCount, sizeof(int), 1, File);

    for (int i = 0; i < ItemCount; ++i)
    {
        CItem* Item = new CItem;

        if (!Item->Init(File))
        {
            SAFE_DELETE(Item);
            return false;
        }

        mOriginItemArray.push_back(Item);
    }

    fclose(File);

    return true;
}

CObjectManager* CObjectManager::GetInst()
{
    if (!mInst)
        mInst = new CObjectManager;

    return mInst;
}

void CObjectManager::DestroyInst()
{
    SAFE_DELETE(mInst);
}
