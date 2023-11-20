#include "pch.h"
#include "CPopeAppear.h"

#include "CLevelMgr.h"
#include "CObj.h"

CPopeAppear::CPopeAppear()
{
}

CPopeAppear::~CPopeAppear()
{
}

void CPopeAppear::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)POPE::SPELL);
	}

}

void CPopeAppear::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	Vec2 vTargetPos = pOwner->GetPos();


	// Player 가 오른쪽에 있을 경우
	if (vTargetPos.x > 2260.f)
	{
		pOwner->SetDir(true);
		pOwner->SetPos(Vec2(1720.f, 1750.f));
	}
	else
	{
		pOwner->SetDir(false);
		pOwner->SetPos(Vec2(2860.f, 1750.f));
	}


	if (pOwner->GetDir())
	{
		pAnimator->Play(L"Appear", false);
	}
	else
	{
		pAnimator->Play(L"Appear_L", false);
	}

}

void CPopeAppear::Exit()
{
}

