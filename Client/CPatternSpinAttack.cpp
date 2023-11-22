#include "pch.h"
#include "CPatternSpinAttack.h"

#include "Pontiff.h"
#include "CGiantSword.h"

CPatternSpinAttack::CPatternSpinAttack()
	: m_fAcc(0.f)
	, m_bAttack(false)

{
}

CPatternSpinAttack::~CPatternSpinAttack()
{
}

void CPatternSpinAttack::finaltick(float _DT)
{
	m_fAcc += _DT;

	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	CGiantSword* pSword = pPontiff->m_pSword;

	if (m_bAttack == false && m_fAcc > 1.f)
	{
		pSword->Spin();
		m_bAttack = true;
	}

	if (m_fAcc > 8.f)
	{
		GetOwnerSM()->ChangeState((UINT)MAPPATTERN::IDLE);
	}


}

void CPatternSpinAttack::Enter()
{
	
	m_bAttack = false;
	m_fAcc = 0.f;
}

void CPatternSpinAttack::Exit()
{
}

