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
        // ����ִ� ������ ã�Ƽ� �������� �߰��Ѵ�.
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
    // �κ��丮 ��ü ������ŭ nullptr�� �̸� ä���д�.
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

        printf("1. ����\n");
        printf("2. ��ȭ\n");
        printf("3. �Ǹ�\n");
        printf("4. �ڷΰ���\n");
        printf("�޴��� �����ϼ��� : ");
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
                printf("����\n");
        }

        printf("0. �ڷΰ���\n");

        // ���������� �� ������� ���
        printf("�������� : ");

        /*if (gPlayer->EquipItem[EEquip::Weapon])
        {
            printf("%s", gPlayer->EquipItem[EEquip::Weapon]->Name);

            if (gPlayer->EquipItem[EEquip::Weapon]->Upgrade > 0)
                printf(" + %d", gPlayer->EquipItem[EEquip::Weapon]->Upgrade);

            printf("\t");
        }

        else*/
            printf("����\t");

        printf("������ : ");

        /*if (gPlayer->EquipItem[EEquip::Armor])
        {
            printf("%s\n", gPlayer->EquipItem[EEquip::Armor]->Name);

            if (gPlayer->EquipItem[EEquip::Armor]->Upgrade > 0)
                printf(" + %d", gPlayer->EquipItem[EEquip::Armor]->Upgrade);

            printf("\t");
        }

        else*/
            printf("����\n");

        printf("������� : %d\n", Player->GetGold());

        printf("�������� �����ϼ��� : ");
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
