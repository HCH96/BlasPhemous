#include "pch.h"
#include "CPenitentPrayStart.h"

CPenitentPrayStart::CPenitentPrayStart()
{
}

CPenitentPrayStart::~CPenitentPrayStart()
{
}

void CPenitentPrayStart::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::PRAYING);
	}
}

void CPenitentPrayStart::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	int iDir = GetOwnerObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"PrayStart", false);
	}
	else
	{
		pAnimator->Play(L"PrayStart_L", false);
	}

}

void CPenitentPrayStart::Exit()
{
}
