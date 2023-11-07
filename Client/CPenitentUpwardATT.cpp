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
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	Vec2 vVel = pMovement->GetVelocity();

	if (pAnimator->GetCurFrame() == 5)
	{
		if (bDir)
		{
			pEffector->PlayNoReset(L"UpwardATT", false);
		}
		else
		{
			pEffector->PlayNoReset(L"UpwardATT_L", false);
		}
	}



	// 상태 변화
	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

}

void CPenitentUpwardATT::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"UpwardAttck", false);
		
	}
	else
	{
		pAnimator->Play(L"UpwardAttck_L", false);
		
	}

	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	pEffector->Play(L"UpwardATT_L", false);
	pEffector->Play(L"UpwardATT", false);
	pEffector->Play(L"None", false);

}

void CPenitentUpwardATT::Exit()
{
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	pEffector->Play(L"None",false);
}



