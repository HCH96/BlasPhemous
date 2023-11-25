#include "pch.h"
#include "CElderBrotherDeath.h"

#include "CLevelMgr.h"
#include "CLevel.h"


CElderBrotherDeath::CElderBrotherDeath()
{
}

CElderBrotherDeath::~CElderBrotherDeath()
{
}


void CElderBrotherDeath::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	pOwner->SetPos(m_vDeathPos);

	if (pAnimator->IsFinish()&& !m_bEnd)
	{
		CLevelMgr::GetInst()->GetCurLevel()->BossDeath();
		m_bEnd = true;
	}


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
	
	m_bEnd = false;

}

void CElderBrotherDeath::Exit()
{
	
}

