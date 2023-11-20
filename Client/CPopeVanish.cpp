#include "pch.h"
#include "CPopeVanish.h"

CPopeVanish::CPopeVanish()
	: m_fAcc(0.f)
{
}

CPopeVanish::~CPopeVanish()
{
}

void CPopeVanish::finaltick(float _DT)
{
	m_fAcc += _DT;

	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish() && m_fAcc > 2.f)
	{
		GetOwnerSM()->ChangeState((UINT)POPE::APPEAR);
	}

}

void CPopeVanish::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	bool bDir = pOwner->GetDir();
	pCollider->SetTime(0.f);

	if (bDir)
	{
		pAnimator->Play(L"Vanish", false);
	}
	else
	{
		pAnimator->Play(L"Vanish_L", false);
	}

	m_fAcc = 0.f;


}

void CPopeVanish::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	pCollider->SetTime(-1.f);
	pCollider->On();
}

