#include "pch.h"
#include "CPontiffOpening.h"

#include "Pontiff.h"

CPontiffOpening::CPontiffOpening()
{
}

CPontiffOpening::~CPontiffOpening()
{
}

void CPontiffOpening::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	if (pPontiff->m_pFace->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PONTIFF::OPENIDLE);
		pPontiff->m_pCollider->SetTime(-1.f);
		pPontiff->m_pCollider->On();
	}

}

void CPontiffOpening::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	pPontiff->m_pBody->Play(L"Opening", false);
	pPontiff->m_pHelmet->Play(L"Opening", false);
	pPontiff->m_pFace->Play(L"Opening", false);
}

void CPontiffOpening::Exit()
{
}

