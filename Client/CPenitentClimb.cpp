#include "pch.h"
#include "CPenitentClimb.h"

CPenitentClimb::CPenitentClimb()
{
}

CPenitentClimb::~CPenitentClimb()
{
}

void CPenitentClimb::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}
	
}

void CPenitentClimb::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	pMovement->SetGround(true);
	int iDir = GetOwnerObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"Climb", false);
	}
	else
	{
		pAnimator->Play(L"Climb_L", false);
	}

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Penitent_EdgeClimb", L"sound\\Object\\Player\\Penitent_EdgeClimb.wav");
	pSound->Play();
}

void CPenitentClimb::Exit()
{
}

