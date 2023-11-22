#include "pch.h"
#include "CPatternIdle.h"

#include "Pontiff.h"

CPatternIdle::CPatternIdle()
	:m_fAcc(0.f)
{
}

CPatternIdle::~CPatternIdle()
{
}

void CPatternIdle::finaltick(float _DT)
{
	m_fAcc += _DT;

	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	if (m_fAcc > 3.f && pPontiff->GetHP() > 0.f)
	{
		UINT iNextPatter = rand() & 5;

		
		//iNextPatter = (UINT)MAPPATTERN::SPINATTACK;

		GetOwnerSM()->ChangeState(iNextPatter);
	}
	
}

void CPatternIdle::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	m_fAcc = 0.f;

}

void CPatternIdle::Exit()
{
}

