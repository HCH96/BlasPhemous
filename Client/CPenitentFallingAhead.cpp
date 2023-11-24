#include "pch.h"
#include "CPenitentFallingAhead.h"

CPenitentFallingAhead::CPenitentFallingAhead()
{
}

CPenitentFallingAhead::~CPenitentFallingAhead()
{
}

void CPenitentFallingAhead::finaltick(float _DT)
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();

	if (pMovement->IsGround())
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_JUMP_FALL_STONE", L"sound\\Object\\Player\\PENITENT_JUMP_FALL_STONE.wav");
		pSound->SetVolume(100.f);
		pSound->Play();

		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::RISING);
	}

}

void CPenitentFallingAhead::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(0.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();

	pAnimator->Play(L"FallingAhead", true);

}

void CPenitentFallingAhead::Exit()
{
}


