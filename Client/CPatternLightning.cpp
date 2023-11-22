#include "pch.h"
#include "CPatternLightning.h"

#include "Pontiff.h"

#include "CLightningSpawner2.h"

CPatternLightning::CPatternLightning()
	: m_fAcc(0.f)
	, m_iCount(0)
{
}

CPatternLightning::~CPatternLightning()
{
}


void CPatternLightning::finaltick(float _DT)
{
	m_fAcc += _DT;

	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	if (m_fAcc > 4.f && m_iCount == 0)
	{
		pPontiff->m_pLightningSpawner->On(Vec2(800.f, 1000.f), true);
		++m_iCount;
	}

	if (m_fAcc > 9.f && m_iCount == 1)
	{
		pPontiff->m_pLightningSpawner->On(Vec2(1880.f, 1000.f), false);
		++m_iCount;
	}

	if (m_fAcc > 13.f)
	{
		GetOwnerSM()->ChangeState((UINT)MAPPATTERN::IDLE);
	}

}

void CPatternLightning::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	pPontiff->m_pSymbolLeft->Play(L"Lightning", false);
	pPontiff->m_pSymbolRight->Play(L"Lightning", false);

	m_fAcc = 0.f;
	m_iCount = 0;
}

void CPatternLightning::Exit()
{
}
