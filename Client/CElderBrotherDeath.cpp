#include "pch.h"
#include "CElderBrotherDeath.h"


CElderBrotherDeath::CElderBrotherDeath()
{
}

CElderBrotherDeath::~CElderBrotherDeath()
{
}


void CElderBrotherDeath::finaltick(float _DT)
{
}

void CElderBrotherDeath::Enter()
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

void CElderBrotherDeath::Exit()
{
}

