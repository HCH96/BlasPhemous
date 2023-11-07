#include "pch.h"
#include "CPenitentCrouching.h"

CPenitentCrouching::CPenitentCrouching()
{
}

CPenitentCrouching::~CPenitentCrouching()
{
}

void CPenitentCrouching::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();
	
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		Enter();
	}

	if (!(KEY_PRESSED(KEY::DOWN)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHUP);
	}

	if (KEY_TAP(KEY::S))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHATT);
	}

}

void CPenitentCrouching::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Crouching", false);
	}
	else
	{
		pAnimator->Play(L"Crouching_L", false);
	}
}

void CPenitentCrouching::Exit()
{
}

