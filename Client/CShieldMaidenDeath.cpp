#include "pch.h"
#include "CShieldMaidenDeath.h"

CShieldMaidenDeath::CShieldMaidenDeath()
{
}

CShieldMaidenDeath::~CShieldMaidenDeath()
{
}

void CShieldMaidenDeath::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		pOwner->Destroy();
	}
}

void CShieldMaidenDeath::Enter()
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

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"SHIELD_ENEMY_DEATH", L"sound\\Object\\Monster\\Normal\\Shieldmaiden\\SHIELD_ENEMY_DEATH.wav");
	pSound->Play();
}

void CShieldMaidenDeath::Exit()
{
}

