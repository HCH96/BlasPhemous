#include "pch.h"
#include "CPenitentRising.h"

CPenitentRising::CPenitentRising()
{
}

CPenitentRising::~CPenitentRising()
{
}

void CPenitentRising::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

}

void CPenitentRising::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();

	pAnimator->Play(L"Rising", false);
}

void CPenitentRising::Exit()
{
}


