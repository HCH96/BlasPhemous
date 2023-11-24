#include "pch.h"
#include "CLionheadDeath.h"


CLionheadDeath::CLionheadDeath()
{
}

CLionheadDeath::~CLionheadDeath()
{
}


void CLionheadDeath::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		pOwner->Destroy();
	}
}

void CLionheadDeath::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	bool bDir = pOwner->GetDir();
	pCollider->SetTime(0.f);
	if (bDir)
	{
		pAnimator->Play(L"Death", false);
	}
	else
	{
		pAnimator->Play(L"Death_L", false);
	}

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"LEON_DEATH", L"sound\\Object\\Monster\\Normal\\LionHead\\LEON_DEATH.wav");
	pSound->Play();

}

void CLionheadDeath::Exit()
{
}

