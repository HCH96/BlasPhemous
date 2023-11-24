#include "pch.h"
#include "CPatternFirebolt.h"

#include "Pontiff.h"
#include "CFireboltSpawner.h"

CPatternFirebolt::CPatternFirebolt()
	: m_fAcc(0.f)
{
}

CPatternFirebolt::~CPatternFirebolt()
{
}

void CPatternFirebolt::finaltick(float _DT)
{
	m_fAcc += _DT;


	if (m_fAcc > 3.f)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_HUSK_RANGED_ATTACK_2.0", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_HUSK_RANGED_ATTACK_2.0.wav");
		pSound->Play();
	}


	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	if (m_fAcc > 2.f && m_iCurSpawner == 0)
	{
		pPontiff->m_vecFireboltSpawner[0]->On(Vec2(750.f, 1030.f));
		++m_iCurSpawner;
	}

	if (m_fAcc > 3.f && m_iCurSpawner == 1)
	{
		pPontiff->m_vecFireboltSpawner[1]->On(Vec2(980.f, 900.f));
		++m_iCurSpawner;
	}

	if (m_fAcc > 4.f && m_iCurSpawner == 2)
	{
		pPontiff->m_vecFireboltSpawner[2]->On(Vec2(1210.f, 900.f));
		++m_iCurSpawner;
	}

	if (m_fAcc > 5.f && m_iCurSpawner == 3)
	{
		pPontiff->m_vecFireboltSpawner[3]->On(Vec2(1470.f, 900.f));
		++m_iCurSpawner;
	}

	if (m_fAcc > 6.f && m_iCurSpawner == 4)
	{
		pPontiff->m_vecFireboltSpawner[4]->On(Vec2(1700.f, 900.f));
		++m_iCurSpawner;
	}

	if (m_fAcc > 7.f && m_iCurSpawner == 5)
	{
		pPontiff->m_vecFireboltSpawner[5]->On(Vec2(1930.f, 1030.f));
		++m_iCurSpawner;
	}





	

	if (m_fAcc > 10.f)
	{
		GetOwnerSM()->ChangeState((UINT)MAPPATTERN::IDLE);
	}

}

void CPatternFirebolt::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	pPontiff->m_pSymbolLeft->Play(L"Firebolt", false);
	pPontiff->m_pSymbolRight->Play(L"Firebolt", false);


	m_iCurSpawner = 0;
	m_fAcc = 0.f;

}

void CPatternFirebolt::Exit()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);


	for (int i = 0; i < pPontiff->m_vecFireboltSpawner.size(); ++i)
	{
		pPontiff->m_vecFireboltSpawner[i]->SetPos(Vec2(0.f, 0.f));
	}
	

}
