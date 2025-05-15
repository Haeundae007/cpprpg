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

void CInventory::Equip(int ItemIndex)
{
    // 아이템 타입을 이용하여 장착부위를 구한다.
    EEquip::Type	EquipType = EEquip::None;

    switch (mItemList[ItemIndex]->GetItemType())
    {
    case EItemType::Weapon:
        EquipType = EEquip::Weapon;
        break;
    case EItemType::Armor:
        EquipType = EEquip::Armor;
        break;
    }

    if (EquipType == EEquip::None)
    {
        printf("장착할 수 없는 아이템입니다.\n");
        system("pause");
        return;
    }

    CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

    // 플레이어에 아이템을 장착한다.
    // 플레이어가 장착하고 있던 아이템을 받아온다.
    CItem* EquipItem = Player->Equip(EquipType, mItemList[ItemIndex]);

    // 인벤토리에 장착하고 있던 아이템을 넣어준다.
    mItemList[ItemIndex] = EquipItem;

    // 기존에 장착하고 있던 아이템이 없을 경우 아이템 수를 줄여준다.
    if (!EquipItem)
        --mItemCount;
}

void CInventory::Upgrade(int ItemIndex)
{
    CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

    // 돈이 부족한지 체크한다.
    if (Player->GetGold() < 1000)
    {
        printf("보유금액이 부족합니다.\n");
        system("pause");
        return;
    }

    // 선택한 아이템의 강화 등급이 최대치인지 확인한다.
    else if (mItemList[ItemIndex]->GetUpgrade() ==
        ITEM_UPGRADE_MAX)
    {
        printf("선택한 아이템의 강화 수치가 최대입니다.\n");
        system("pause");
        return;
    }

    // 돈을 차감한다.
    Player->AddGold(-1000);

    // 선택한 아이템의 강화 등급에 맞는 확률을 가져온다.
    float Rate = mUpgradeRate[mItemList[ItemIndex]->GetUpgrade()];

    float Percent = rand() % 10000 / 100.f;

    if (Percent < Rate)
    {
        printf("강화 성공\n");

        int AddOption = (int)(mItemList[ItemIndex]->GetOption() * 0.1f);
        int AddSell = (int)(mItemList[ItemIndex]->GetSell() * 0.1f);

        mItemList[ItemIndex]->UpgradeSuccess(1, AddOption, AddSell);
    }

    else
    {
        printf("강화실패\n");
    }

    system("pause");
}

void CInventory::Sell(int ItemIndex)
{
    // 아이템이 없을 경우
    if (!mItemList[ItemIndex])
    {
        printf("판매할 아이템이 없습니다.\n");
        system("pause");
        return;
    }

    CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

    // 플레이어 보유금액을 증가시킨다.
    Player->AddGold(mItemList[ItemIndex]->GetSell());

    // 아이템을 제거한다.
    SAFE_DELETE(mItemList[ItemIndex]);

    --mItemCount;
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
            Equip(ItemIndex);
            return;
        case EInventoryMenu::Upgrade:
            Upgrade(ItemIndex);
            break;
        case EInventoryMenu::Sell:
            Sell(ItemIndex);
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

        if (Player->GetEquipItem(EEquip::Weapon))
        {
            printf("%s", Player->GetEquipItem(EEquip::Weapon)->GetName());

            if (Player->GetEquipItem(EEquip::Weapon)->GetUpgrade() > 0)
                printf(" + %d", Player->GetEquipItem(EEquip::Weapon)->GetUpgrade());

            printf("\t");
        }

        else
            printf("없음\t");

        printf("장착방어구 : ");

        if (Player->GetEquipItem(EEquip::Armor))
        {
            printf("%s\n", Player->GetEquipItem(EEquip::Armor)->GetName());

            if (Player->GetEquipItem(EEquip::Armor)->GetUpgrade() > 0)
                printf(" + %d", Player->GetEquipItem(EEquip::Armor)->GetUpgrade());

            printf("\t");
        }

        else
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
