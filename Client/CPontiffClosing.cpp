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
	CObj* pOwner = GetOwnerObj;
	Pontiff* pPontiff = dynamic_cast<Pontiff*>(pOwner);

	CGiantSword* pSword = pPontiff->m_pSword;

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

}

void CPontiffClosing::Exit()
{
}
