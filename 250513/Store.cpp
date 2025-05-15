#include "Store.h"
#include "ObjectManager.h"
#include "Item.h"
#include "Player.h"
#include "Inventory.h"

CStore::CStore()
{
}

CStore::~CStore()
{
}

bool CStore::Init(EStoreType::Type StoreType)
{
    mStoreType = StoreType;

    CObjectManager::GetInst()->AddStoreItem(mItemList, StoreType);

    return true;
}

void CStore::Run()
{
    CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

    while (true)
    {
        system("cls");

        switch (mStoreType)
        {
        case EStoreType::Weapon:
            printf("============== 무기상점 ==============\n");
            break;
        case EStoreType::Armor:
            printf("============== 방어구상점 ==============\n");
            break;
        }

        int Size = mItemList.size();

        for (int i = 0; i < Size; ++i)
        {
            printf("%d. %s\n", i + 1, mItemList[i]->GetName());
        }

        printf("%d. 뒤로가기\n", Size + 1);

        printf("보유골드 : %d\n", Player->GetGold());
        printf("구매할 아이템을 선택하세요 : ");
        int	Input = 0;
        scanf_s("%d", &Input);

        if (Input <= 0 || Input > Size + 1)
            continue;

        else if (Input == Size + 1)
            return;

        // 선택한 아이템 번호를 상점의 인덱스로 변경한다.
        int	StoreIndex = Input - 1;

        // 플레이어가 보유한 금액이 부족한지 체크한다.
        if (Player->GetGold() < mItemList[StoreIndex]->GetPrice())
        {
            printf("보유금액이 부족합니다.\n");
            system("pause");
            continue;
        }

        // 인벤토리 칸 부족한지 체크
        else if (CInventory::GetInst()->IsFull())
        {
            printf("인벤토리 공간이 부족합니다.\n");
            system("pause");
            continue;
        }

        // 아이템 생성
        CItem* NewItem = mItemList[StoreIndex]->Clone();

        // 인벤토리에 추가
        CInventory::GetInst()->AddItem(NewItem);

        // 플레이어 보유금액 차감.
        Player->AddGold(-mItemList[StoreIndex]->GetPrice());

        printf("%s 아이템을 구매하였습니다.\n", NewItem->GetName());
        system("pause");
    }
}
