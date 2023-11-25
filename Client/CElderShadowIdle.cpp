#include "pch.h"
#include "CElderShadowIdle.h"

CElderShadowIdle::CElderShadowIdle()
{
}

CElderShadowIdle::~CElderShadowIdle()
{
}

void CElderShadowIdle::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)ELDERBROTHER::JUMP);
		
	}

}

void CElderShadowIdle::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Vec2 vPos = pOwner->GetPos();

	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Idle", false);
	}
	else
	{
		pAnimator->Play(L"Idle_L", false);
	}

}

void CElderShadowIdle::Exit()
{
}

