#include "pch.h"
#include "CPenitentLadderDown.h"

CPenitentLadderDown::CPenitentLadderDown()
{
}

CPenitentLadderDown::~CPenitentLadderDown()
{
}

void CPenitentLadderDown::finaltick(float _DT)
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::LADDER);
	}
}

void CPenitentLadderDown::Enter()
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();
	CMovement* pMovement = pObj->GetComponent<CMovement>();
	pMovement->SetVelocity(Vec2(0.f, 0.f));
	pMovement->UseGravity(false);
	int iDir = pObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"LadderDown", false);
	}
	else
	{
		pAnimator->Play(L"LadderDown_L", false);
	}
}

void CPenitentLadderDown::Exit()
{
}
