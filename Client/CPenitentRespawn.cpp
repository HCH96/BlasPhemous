#include "pch.h"
#include "CPenitentRespawn.h"

CPenitentRespawn::CPenitentRespawn()
{
}

CPenitentRespawn::~CPenitentRespawn()
{
}

void CPenitentRespawn::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

}

void CPenitentRespawn::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");

	int iDir = GetOwnerObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"Respawn", false);
		pEffector->Play(L"Respawn", false);
	}
	else
	{
		pAnimator->Play(L"Respawn_L", false);
		pEffector->Play(L"Respawn_L", false);
	}
	

	//CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"CHECKPOINT_KNEEL_DOWN_FINISH", L"sound\\Effect\\CHECKPOINT_KNEEL_DOWN_FINISH.wav");
	//pSound->Play();

}

void CPenitentRespawn::Exit()
{
}

