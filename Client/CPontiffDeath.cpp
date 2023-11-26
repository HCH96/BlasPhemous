#include "pch.h"
#include "CPontiffDeath.h"

#include "Pontiff.h"
#include "CGiantSword.h"


CPontiffDeath::CPontiffDeath()
{
}

CPontiffDeath::~CPontiffDeath()
{
}

void CPontiffDeath::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	if (pPontiff->m_pFace->IsFinish() && !m_bEnd)
	{
		CLevelMgr::GetInst()->GetCurLevel()->BossDeath();
		m_bEnd = true;
	}

}

void CPontiffDeath::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	pPontiff->m_pBody->Play(L"Closing", false);
	pPontiff->m_pHelmet->Play(L"Closing", false);
	pPontiff->m_pFace->Play(L"Death", false);

	pPontiff->m_pCollider->SetTime(0.f);


	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_DEATH", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_DEATH.wav");
	pSound->Play();

	m_bEnd = false;
}

void CPontiffDeath::Exit()
{
}

