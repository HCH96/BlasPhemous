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
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"CHECKPOINT_KNEEL_DOWN_FINISH", L"sound\\Effect\\CHECKPOINT_KNEEL_DOWN_FINISH.wav");
	pSound->Play();

}

void CPenitentPrayEnd::Exit()
{
}


