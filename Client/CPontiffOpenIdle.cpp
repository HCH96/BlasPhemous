#include "pch.h"
#include "CPontiffOpenIdle.h"

#include "Pontiff.h"

CPontiffOpenIdle::CPontiffOpenIdle()
	: m_fAcc(0.f)
{
}

CPontiffOpenIdle::~CPontiffOpenIdle()
{
}

void CPontiffOpenIdle::finaltick(float _DT)
{
	m_fAcc += _DT;

	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	// Death
	if (pPontiff->GetHP() < 0.f)
	{
		
		GetOwnerSM()->ChangeState((UINT)PONTIFF::DEATH);
	}

	// Closing
	if (m_fAcc > 11.f)
	{

		GetOwnerSM()->ChangeState((UINT)PONTIFF::CLOSING);
	}

}

void CPontiffOpenIdle::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	m_fAcc = 0.f;

	pPontiff->m_pBody->Play(L"Idle", true);
	pPontiff->m_pHelmet->Play(L"Idle", true);
	pPontiff->m_pFace->Play(L"OpenIdle", true);

}

void CPontiffOpenIdle::Exit()
{
}
