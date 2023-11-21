#include "pch.h"
#include "CGiantSwordVanish.h"


CGiantSwordVanish::CGiantSwordVanish()
	: m_fDeadTime(0.f)
{
}

CGiantSwordVanish::~CGiantSwordVanish()
{
}


void CGiantSwordVanish::finaltick(float _DT)
{
	m_fDeadTime += _DT;
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		pAnimator->Stop();
	}

	if (m_fDeadTime > 20.f)
	{
		GetOwnerSM()->ChangeState((UINT)GIANTSWORD::APPEAR);
	}


}

void CGiantSwordVanish::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CAnimator* pEye = pOwner->GetComponent<CAnimator>(L"GiantSwordEye");
	CCollider* pCollider = pOwner->GetComponent<CCollider>();


	pCollider->SetTime(0.f);
	m_fDeadTime = 0.f;



	pAnimator->Play(L"Vanish", false);
	pCollider->SetTime(0.f);
	pEye->Stop();
}

void CGiantSwordVanish::Exit()
{
}

