#include "pch.h"
#include "CPenitentUpwardATT.h"

CPenitentUpwardATT::CPenitentUpwardATT()
{
}

CPenitentUpwardATT::~CPenitentUpwardATT()
{
}

void CPenitentUpwardATT::finaltick(float _DT)
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();

	Vec2 vVel = pMovement->GetVelocity();

	// 상태 변화
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		Enter();
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

}

void CPenitentUpwardATT::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"UpwardAttck", false);
	}
	else
	{
		pAnimator->Play(L"UpwardAttck_L", false);
	}
}

void CPenitentUpwardATT::Exit()
{
}



