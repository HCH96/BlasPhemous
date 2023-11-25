#include "pch.h"
#include "CElderBrotherDeath.h"


CElderBrotherDeath::CElderBrotherDeath()
{
}

CElderBrotherDeath::~CElderBrotherDeath()
{
}


void CElderBrotherDeath::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	pOwner->SetPos(m_vDeathPos);

}

void CElderBrotherDeath::Enter()
{
	CObj* pOwner = GetOwnerObj;
	m_vDeathPos = pOwner->GetPos();
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

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_DEATH", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_DEATH.wav");
	pSound->Play();

	pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_DEATH_VOICE_2", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_DEATH_VOICE_2.wav");
	pSound->Play();

	pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_BOSS_DEATH_HIT", L"sound\\Object\\Player\\PENITENT_BOSS_DEATH_HIT.wav");
	pSound->Play();
	
}

void CElderBrotherDeath::Exit()
{
}

