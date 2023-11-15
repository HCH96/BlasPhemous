#include "pch.h"
#include "CPenitentLadderUp.h"

CPenitentLadderUp::CPenitentLadderUp()
{
}

CPenitentLadderUp::~CPenitentLadderUp()
{
}
void CPenitentLadderUp::finaltick(float _DT)
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}
}

void CPenitentLadderUp::Enter()
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();
	CMovement* pMovement = pObj->GetComponent<CMovement>();
	pMovement->SetVelocity(Vec2(0.f, 0.f));
	pMovement->UseGravity(false);
	int iDir = pObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"LadderUp", false);
	}
	else
	{
		pAnimator->Play(L"LadderUp_L", false);
	}
}

void CPenitentLadderUp::Exit()
{
	CObj* pObj = GetOwnerObj;
	CMovement* pMovement = pObj->GetComponent<CMovement>();
	pMovement->UseGravity(true);
	pMovement->SetGround(true);
}



