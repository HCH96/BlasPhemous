#include "pch.h"
#include "CPontiffClosing.h"

#include "Pontiff.h"
#include "CGiantSword.h"

CPontiffClosing::CPontiffClosing()
{
}

CPontiffClosing::~CPontiffClosing()
{
}

void CPontiffClosing::finaltick(float _DT)
{
	if (!m_bSound)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_MASK_CLOSE", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_MASK_CLOSE.wav");
		pSound->Play();

		m_bSound = true;
	}

	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	CGiantSword* pSword = pPontiff->m_pSword;

	// Death
	if (pPontiff->GetHP() < 0.f)
	{
		
		GetOwnerSM()->ChangeState((UINT)PONTIFF::DEATH);
	}

	if (!pSword->GetActive())
	{
		GetOwnerSM()->ChangeState((UINT)PONTIFF::OPENING);
	}
}

void CPontiffClosing::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	pPontiff->m_pBody->Play(L"Closing", false);
	pPontiff->m_pHelmet->Play(L"Closing", false);
	pPontiff->m_pFace->Play(L"Closing", false);

	pPontiff->m_pCollider->SetTime(0.f);

	m_bSound = false;

}

void CPontiffClosing::Exit()
{
}
