#include "pch.h"
#include "CPenitentFallingAhead.h"

CPenitentFallingAhead::CPenitentFallingAhead()
{
}

CPenitentFallingAhead::~CPenitentFallingAhead()
{
}

void CPenitentFallingAhead::finaltick(float _DT)
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();

	if (pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::RISING);
	}

}

void CPenitentFallingAhead::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();

	pAnimator->Play(L"FallingAhead", true);

}

void CPenitentFallingAhead::Exit()
{
}


