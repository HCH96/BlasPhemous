#include "pch.h"
#include "CPenitentCrouchATT.h"

CPenitentCrouchATT::CPenitentCrouchATT()
	: m_bDir(true)
{
}

CPenitentCrouchATT::~CPenitentCrouchATT()
{
}

void CPenitentCrouchATT::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bCurDir = GetOwnerObj->GetDir();


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHING);
	}
}

void CPenitentCrouchATT::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		m_bDir = bDir;
		pAnimator->Play(L"CrouchATT", false);
	}
	else
	{
		m_bDir = bDir;
		pAnimator->Play(L"CrouchATT_L", false);
	}
}

void CPenitentCrouchATT::Exit()
{
}
