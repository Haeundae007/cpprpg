#include "Player.h"
#include "ObjectManager.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    // 직업정보 파일을 읽어온다.
    FPlayerEditorInfo	JobInfo[3] = {};

    FILE* File = nullptr;

    fopen_s(&File, "PlayerInfo.pli", "rb");

    if (!File)
        return false;

    fread(JobInfo, sizeof(FPlayerEditorInfo), 3, File);

    fclose(File);

    // 플레이어 이름을 입력하고 직업을 선택한다.
    printf("이름 : ");
    scanf_s("%s", mName, 31);

    printf("1. 기사\n");
    printf("2. 궁수\n");
    printf("3. 마법사\n");
    printf("직업을 선택하세요 : ");
    int	Input = 0;
    scanf_s("%d", &Input);

    if (Input <= (int)EPlayerJob::None ||
        Input >= (int)EPlayerJob::End)
        return false;

    mJob = (EPlayerJob)Input;

    mAttack = JobInfo[Input - 1].Attack;
    mDefense = JobInfo[Input - 1].Defense;
    mHPMax = JobInfo[Input - 1].HP;
    mHP = mHPMax;
    mMPMax = JobInfo[Input - 1].MP;
    mMP = mMPMax;

	return true;
}

bool CPlayer::Init(const char* Name, EPlayerJob Job,
	const FPlayerEditorInfo& JobInfo)
{
    strcpy_s(mName, Name);

    mJob = Job;

    mAttack = JobInfo.Attack;
    mDefense = JobInfo.Defense;
    mHPMax = JobInfo.HP;
    mHP = mHPMax;
    mMPMax = JobInfo.MP;
    mMP = mMPMax;

	return true;
}

void CPlayer::Output()
{
	printf("이름 : %s\t직업 : ", mName);

	switch (mJob)
	{
	case EPlayerJob::Knight:
		printf("기사\n");
		break;
	case EPlayerJob::Archer:
		printf("궁수\n");
		break;
	case EPlayerJob::Magicion:
		printf("마법사\n");
		break;
	}

	int	LevelExp = CObjectManager::GetInst()->GetLevelExp(mLevel);

	printf("레벨 : %d\t경험치 : %d / %d\n", mLevel,
		mExp, LevelExp);
	/*printf("공격력 : %d\t방어력 : %d\n", gPlayer->Attack,
		gPlayer->Defense);*/

	printf("공격력 : %d", mAttack);

	/*if (gPlayer->EquipItem[EEquip::Weapon])
		printf(" + %d", gPlayer->EquipItem[EEquip::Weapon]->Option);*/

	printf("\t방어력 : %d", mDefense);

	/*if (gPlayer->EquipItem[EEquip::Armor])
		printf(" + %d", gPlayer->EquipItem[EEquip::Armor]->Option);*/

	printf("\n");

	printf("체력 : %d / %d\t마나 : %d / %d\n",
		mHP, mHPMax,
		mMP, mMPMax);
	printf("골드 : %d\n", mGold);

	printf("장착무기 : ");

	/*if (gPlayer->EquipItem[EEquip::Weapon])
		printf("%s\t", gPlayer->EquipItem[EEquip::Weapon]->Name);

	else*/
		printf("없음\t");

	printf("장착방어구 : ");

	/*if (gPlayer->EquipItem[EEquip::Armor])
		printf("%s\n", gPlayer->EquipItem[EEquip::Armor]->Name);

	else*/
		printf("없음\n");
}

void CPlayer::LevelUp()
{
	int	LevelExp = CObjectManager::GetInst()->GetLevelExp(mLevel);

	if (mExp >= LevelExp)
	{
		mExp -= LevelExp;

		++mLevel;

		mAttack = (int)(mAttack * 1.1f);
		mDefense = (int)(mDefense * 1.1f);
		mHPMax = (int)(mHPMax * 1.1f);
		mMPMax = (int)(mMPMax * 1.1f);

		mHP = mHPMax;
		mMP = mMPMax;

		printf("레벨이 올랐습니다.\n");
	}
}
