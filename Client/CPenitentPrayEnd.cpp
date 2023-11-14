#include "pch.h"
#include "CPenitentPrayEnd.h"

CPenitentPrayEnd::CPenitentPrayEnd()
{
}

CPenitentPrayEnd::~CPenitentPrayEnd()
{
}


void CPenitentPrayEnd::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

}

void CPenitentPrayEnd::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	int iDir = GetOwnerObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"PrayEnd", false);
	}
	else
	{
		pAnimator->Play(L"PrayEnd_L", false);
	}
}

void CPenitentPrayEnd::Exit()
{
}


