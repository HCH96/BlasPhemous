#include "pch.h"
#include "CPenitentPraying.h"

CPenitentPraying::CPenitentPraying()
{
}

CPenitentPraying::~CPenitentPraying()
{
}

void CPenitentPraying::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::PRAYAURAOFF);
	}
}

void CPenitentPraying::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	int iDir = GetOwnerObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"Praying", true);
	}
	else
	{
		pAnimator->Play(L"Praying_L", true);
	}
}

void CPenitentPraying::Exit()
{
}