#include "Battle.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"

namespace EBattleMenu
{
	enum Type
	{
		None,
		Attack,
		Back,
		End
	};
}

CBattle::CBattle()
{
}

CBattle::~CBattle()
{
}

bool CBattle::Init(EMapMenu Map)
{
	mMap = Map;

    return true;
}

EBattleResult CBattle::Battle(CPlayer* Player, CMonster* Monster)
{
	// 플레이어가 몬스터를 공격한다.
	// 장착 무기가 있을 경우 추가 공격력이 적용되어야 한다.
	int	Attack = Player->GetAttack();

	/*if (gPlayer->EquipItem[EEquip::Weapon])
		Attack += gPlayer->EquipItem[EEquip::Weapon]->Option;*/

	int	Damage = Attack - Monster->GetDefense();

	// 최소데미지가 1은 들어갈 수 있게 한다.
	// 삼항연산자 : 왼쪽의 조건식이 true일 경우 : 왼쪽의 값이 반환되고
	// false일 경우 : 오른쪽의 값이 반환된다.
	Damage = Damage <= 0 ? 1 : Damage;
	/*if (Damage <= 0)
		Damage = 1;*/

	printf("Player가 Monster에게 %d 데미지를 주었습니다.\n", Damage);

	if (!Monster->Damage(Damage))
	{
		// 경험치와 골드를 습득하게 한다.
		Player->AddExp(Monster->GetExp());
		Player->AddGold(Monster->GetGold());

		printf("Monster가 죽었습니다.\n");

		// 인벤토리에 공간이 있을 경우에만 아이템을 획득할 수 있게 한다.
		//if (gInventory->Count < INVENTORY_MAX)
		//{
		//	// 아이템을 드랍할 확률을 구한다.
		//	float	Percent = rand() % 10000 / 100.f;

		//	// 20% 확률로 아이템을 획득한다.
		//	if (Percent < 20.f)
		//	{
		//		// 어떤 아이템을 드랍할지 결정한다.
		//		int	DropIndex = rand() % gItemListCount;

		//		FItem* DropItem = new FItem;

		//		*DropItem = gItemList[DropIndex];

		//		// 인벤토리의 빈 공간을 찾아 아이템을 넣어준다.
		//		for (int i = 0; i < INVENTORY_MAX; ++i)
		//		{
		//			if (!gInventory->ItemList[i])
		//			{
		//				gInventory->ItemList[i] = DropItem;
		//				++gInventory->Count;
		//				break;
		//			}
		//		}

		//		printf("%s 아이템을 획득하였습니다.\n",
		//			DropItem->Name);
		//		system("pause");
		//	}
		//}


		// 레벨업 했는지 확인.
		Player->LevelUp();

		system("pause");

		return EBattleResult::MonsterDeath;
	}

	// 몬스터가 플레이어를 공격한다.
	// 장착방어구가 있을 경우 추가 방어력을 적용한다.
	int	Defense = Player->GetDefense();

	/*if (gPlayer->EquipItem[EEquip::Armor])
		Defense += gPlayer->EquipItem[EEquip::Armor]->Option;*/

	Damage = Monster->GetAttack() - Defense;

	Damage = Damage <= 0 ? 1 : Damage;

	printf("Monster가 Player에게 %d 데미지를 주었습니다.\n", Damage);

	if (!Player->Damage(Damage))
	{
		// 플레이어가 죽었을 경우 경험치와 골드를 10% 감소시키고
		// 체력과 마나를 최대치로 하여 부활시킨다.
		Player->AddExp(Player->GetExp() * -0.1f);
		Player->AddGold(Player->GetGold() * -0.1f);

		Player->Restore();

		printf("Player가 죽었습니다.\n");

		system("pause");

		return EBattleResult::PlayerDeath;
	}

	system("pause");

	return EBattleResult::None;
}

void CBattle::Run()
{
	CPlayer* Player = CObjectManager::GetInst()->GetPlayer();
	CMonster* Monster = CObjectManager::GetInst()->CloneMonster(mMap);

    while (true)
    {
		system("cls");
		printf("================ Player ================\n");
		Player->Output();

		printf("================ Monster ================\n");
		Monster->Output();

		// 전투 메뉴
		printf("1. 공격\n");
		printf("2. 도망가기\n");
		printf("메뉴를 선택하세요 : ");
		int	Input;
		scanf_s("%d", &Input);

		switch (Input)
		{
		case EBattleMenu::Attack:
			if (Battle(Player, Monster) == EBattleResult::MonsterDeath)
			{
				//Monster->HP = Monster->HPMax;
				//Monster->MP = Monster->MPMax;
				// 죽은 몬스터를 제거하고 다시 생성한다.
				SAFE_DELETE(Monster);

				Monster = CObjectManager::GetInst()->CloneMonster(mMap);
			}
			break;
		case EBattleMenu::Back:
			// 여기서 메모리 제거가 없을 경우 메모리 릭이 남게 된다.
			SAFE_DELETE(Monster);
			return;
		}
    }
}
