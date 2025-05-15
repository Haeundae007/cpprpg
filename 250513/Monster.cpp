#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::CMonster(const CMonster& Monster)
{
    *this = Monster;
}

CMonster::~CMonster()
{
}

bool CMonster::Init(const FMonsterEditorInfo& Info)
{
    strcpy_s(mName, Info.Name);
    mAttack = Info.Attack;
    mDefense = Info.Defense;
    mHP = Info.HP;
    mHPMax = Info.HP;
    mMP = Info.MP;
    mMPMax = Info.MP;
    mLevel = Info.Level;
    mExp = Info.Exp;
    mGold = Info.Gold;

    return true;
}

void CMonster::Output()
{
    printf("이름 : %s\t레벨 : %d\n", mName,
        mLevel);

    printf("획득경험치 : %d\t획득골드 : %d\n", mExp,
        mGold);
    printf("공격력 : %d\t방어력 : %d\n", mAttack,
        mDefense);
    printf("체력 : %d / %d\t마나 : %d / %d\n",
        mHP, mHPMax,
        mMP, mMPMax);
}

CMonster* CMonster::Clone()
{
    // new CMonster를 해서 새로운 객체를 만든다.
    // 이때 *this을 해주어서 이 함수를 호출한 객체를 인자로 전달하여
    // 복사생성자에서 그대로 데이터를 복사하고 생성된 객체의 주소를
    // 반환해준다.
    return new CMonster(*this);
}
