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
	bool bDir = pOwner->GetDir();

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

