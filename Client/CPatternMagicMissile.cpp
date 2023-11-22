#include "pch.h"
#include "CPatternMagicMissile.h"

#include "CMagicMissileSpawner2.h"
#include "Pontiff.h"

CPatternMagicMissile::CPatternMagicMissile()
{
}

CPatternMagicMissile::~CPatternMagicMissile()
{
}

void CPatternMagicMissile::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	if (pPontiff->m_pSymbolLeft->IsFinish() && pPontiff->m_pSymbolRight->IsFinish())
	{
		pPontiff->m_pSymbolLeft->Stop();
		pPontiff->m_pSymbolRight->Stop();


		pPontiff->m_vecMagicMissileSpawner[0]->On(Vec2(1050.f, 500.f));
		pPontiff->m_vecMagicMissileSpawner[1]->On(Vec2(1630.f, 500.f));
	}


	m_fAcc += _DT;

	if (m_fAcc > 10.f)
	{
		GetOwnerSM()->ChangeState((UINT)MAPPATTERN::IDLE);
	}

}

void CPatternMagicMissile::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	pPontiff->m_pSymbolLeft->Play(L"MagicMissile", false);
	pPontiff->m_pSymbolRight->Play(L"MagicMissile", false);

	m_fAcc = 0.f;

}

void CPatternMagicMissile::Exit()
{
}

