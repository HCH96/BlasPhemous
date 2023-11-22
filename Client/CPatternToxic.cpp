#include "pch.h"
#include "CPatternToxic.h"

#include "Pontiff.h"

#include "CToxicSpawner.h"

CPatternToxic::CPatternToxic()
{
}

CPatternToxic::~CPatternToxic()
{
}

void CPatternToxic::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	if (pPontiff->m_pSymbolLeft->IsFinish() && pPontiff->m_pSymbolRight->IsFinish())
	{
		pPontiff->m_pSymbolLeft->Stop();
		pPontiff->m_pSymbolRight->Stop();

		pPontiff->m_pToxicSpawner->On(Vec2(1340.f, 850.f));
	}
	

	m_fAcc += _DT;

	if (m_fAcc > 10.f)
	{
		GetOwnerSM()->ChangeState((UINT)MAPPATTERN::IDLE);
	}
}

void CPatternToxic::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	pPontiff->m_pSymbolLeft->Play(L"Toxic", false);
	pPontiff->m_pSymbolRight->Play(L"Toxic", false);


	m_fAcc = 0.f;

}

void CPatternToxic::Exit()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	pPontiff->m_pToxicSpawner->SetPos(Vec2(0.f, 0.f));

}

