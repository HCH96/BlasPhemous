#include "pch.h"
#include "CPenitentCrouch.h"

CPenitentCrouch::CPenitentCrouch()
{
}

CPenitentCrouch::~CPenitentCrouch()
{
}


void CPenitentCrouch::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();
	UINT iCurFrame = (UINT)pAnimator->GetCurFrame();


	// 방향 전환
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		if (bDir)
		{
			pAnimator->PlayFromFrame(L"Crouch", iCurFrame, false);
		}
		else
		{
			pAnimator->PlayFromFrame(L"Crouch_L", iCurFrame, false);
		}
	}

	// 상태 전환
	if ( (KEY_PRESSED(KEY::S) || KEY_TAP(KEY::S)) && pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHATT);
	}

	if (KEY_TAP(KEY::D))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DODGE);
	}
	
	if (!(KEY_PRESSED(KEY::DOWN)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHUP);
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHING);
	}


}

void CPenitentCrouch::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Crouch", false);
	}
	else
	{
		pAnimator->Play(L"Crouch_L", false);
	}
}

void CPenitentCrouch::Exit()
{
}

