#include "pch.h"
#include "CPenitentPraying.h"

CPenitentPraying::CPenitentPraying()
{
}

CPenitentPraying::~CPenitentPraying()
{
}

void CPenitentPraying::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::PRAYAURAOFF);
	}
}

void CPenitentPraying::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	int iDir = GetOwnerObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"Praying", true);
	}
	else
	{
		pAnimator->Play(L"Praying_L", true);
	}

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"CHECKPOINT_KNEEL_DOWN", L"sound\\Effect\\CHECKPOINT_KNEEL_DOWN.wav");
	pSound->Play();
}

void CPenitentPraying::Exit()
{
}