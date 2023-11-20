#include "pch.h"
#include "CFoolKnifeDeath.h"

CFoolKnifeDeath::CFoolKnifeDeath()
{
}

CFoolKnifeDeath::~CFoolKnifeDeath()
{
}


void CFoolKnifeDeath::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		pOwner->Destroy();
	}
}

void CFoolKnifeDeath::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	bool bDir = pOwner->GetDir();

	pCollider->SetTime(0.f);

	if (bDir)
	{
		pAnimator->Play(L"Death", true);
	}
	else
	{
		pAnimator->Play(L"Death_L", true);
	}
}

void CFoolKnifeDeath::Exit()
{
	
}
