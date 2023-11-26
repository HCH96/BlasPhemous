#include "pch.h"
#include "CPopeDeath.h"

CPopeDeath::CPopeDeath()
{
}

CPopeDeath::~CPopeDeath()
{
}

void CPopeDeath::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish() && !m_bEnd)
	{
		CLevelMgr::GetInst()->GetCurLevel()->BossDeath();
		m_bEnd = true;
	}

}

void CPopeDeath::Enter()
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

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_DEATH", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_DEATH.wav");
	pSound->Play();


	m_bEnd = false;
}

void CPopeDeath::Exit()
{
}

