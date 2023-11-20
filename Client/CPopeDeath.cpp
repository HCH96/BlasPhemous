#include "pch.h"
#include "CPopeDeath.h"

CPopeDeath::CPopeDeath()
{
}

CPopeDeath::~CPopeDeath()
{
}

void CPopeDeath::finaltick(float _DT)
{
}

void CPopeDeath::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	bool bDir = pOwner->GetDir();
	pCollider->SetTime(0.f);
	if (bDir)
	{
		pAnimator->Play(L"Death", false);
	}
	else
	{
		pAnimator->Play(L"Death_L", false);
	}

}

void CPopeDeath::Exit()
{
}

