#include "pch.h"
#include "CLionheadAttack.h"

CLionheadAttack::CLionheadAttack()
{
}

CLionheadAttack::~CLionheadAttack()
{
}

void CLionheadAttack::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	bool bDir = pOwner->GetDir();


	CCollider* pHitBox = pOwner->GetComponent<CCollider>(L"Mon_HitBox");
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->GetCurFrame() == 10)
	{
		pHitBox->On();
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)LIONHEAD::IDLE);
	}

}

void CLionheadAttack::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pHitBox = pOwner->GetComponent<CCollider>(L"Mon_HitBox");
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Attack", false);
		pHitBox->SetOffsetPos(Vec2(130.f, -70.f));
	}
	else
	{
		pAnimator->Play(L"Attack_L", false);
		pHitBox->SetOffsetPos(Vec2(-130.f, -70.f));
	}
}

void CLionheadAttack::Exit()
{
}
