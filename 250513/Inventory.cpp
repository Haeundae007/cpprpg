#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ObjectManager.h"

namespace EInventoryMenu
{
    enum Type
    {
        None,
        Equip,
        Upgrade,
        Sell,
        Back,
        End
    };
}

CInventory* CInventory::mInst = nullptr;

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
    for (int i = 0; i < mItemMaxCount; ++i)
    {
        SAFE_DELETE(mItemList[i]);
    }
}

void CInventory::AddItem(CItem* Item)
{
    for (int i = 0; i < mItemMaxCount; ++i)
    {
        // 비어있는 공간을 찾아서 아이템을 추가한다.
        if (!mItemList[i])
        {
            mItemList[i] = Item;
            ++mItemCount;
            break;
        }
    }
}

bool CInventory::Init()
{
    // 인벤토리 전체 공간만큼 nullptr로 미리 채워둔다.
    for (int i = 0; i < mItemMaxCount; ++i)
    {
        mItemList.push_back(nullptr);
    }

    return true;
}

void CInventory::RunItem(int ItemIndex)
{
    if (!mItemList[ItemIndex])
        return;

    while (true)
    {
        system("cls");

        mItemList[ItemIndex]->Output();
        printf("\n");

        printf("1. 장착\n");
        printf("2. 강화\n");
        printf("3. 판매\n");
        printf("4. 뒤로가기\n");
        printf("메뉴를 선택하세요 : ");
        int	Input = 0;
        scanf_s("%d", &Input);

        if (Input <= EInventoryMenu::None ||
            Input >= EInventoryMenu::End)
            continue;

        else if (Input == EInventoryMenu::Back)
            break;

        switch (Input)
        {
        case EInventoryMenu::Equip:
            //Equip(ItemIndex);
            return;
        case EInventoryMenu::Upgrade:
            //Upgrade(ItemIndex);
            break;
        case EInventoryMenu::Sell:
            //ItemSell(ItemIndex);
            return;
        }
    }
}

void CInventory::Run()
{
    CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

    while (true)
    {
        system("cls");

        for (int i = 0; i < mItemMaxCount; ++i)
        {
            printf("%d. ", i + 1);

            if (mItemList[i])
                mItemList[i]->Output();

            else
                printf("없음\n");
        }

        printf("0. 뒤로가기\n");

        // 장착아이템 및 보유골드 출력
        printf("장착무기 : ");

        /*if (gPlayer->EquipItem[EEquip::Weapon])
        {
            printf("%s", gPlayer->EquipItem[EEquip::Weapon]->Name);

            if (gPlayer->EquipItem[EEquip::Weapon]->Upgrade > 0)
                printf(" + %d", gPlayer->EquipItem[EEquip::Weapon]->Upgrade);

            printf("\t");
        }

        else*/
            printf("없음\t");

        printf("장착방어구 : ");

        /*if (gPlayer->EquipItem[EEquip::Armor])
        {
            printf("%s\n", gPlayer->EquipItem[EEquip::Armor]->Name);

            if (gPlayer->EquipItem[EEquip::Armor]->Upgrade > 0)
                printf(" + %d", gPlayer->EquipItem[EEquip::Armor]->Upgrade);

            printf("\t");
        }

        else*/
            printf("없음\n");

        printf("보유골드 : %d\n", Player->GetGold());

        printf("아이템을 선택하세요 : ");
        int	Input = 0;
        scanf_s("%d", &Input);

        if (Input == 0)
            break;

        else if (Input < 0 || Input > mItemMaxCount)
            continue;

        RunItem(Input - 1);
    }
}

CInventory* CInventory::GetInst()
{
    if (!mInst)
        mInst = new CInventory;

    return mInst;
}

void CInventory::DestroyInst()
{
    SAFE_DELETE(mInst);
}
