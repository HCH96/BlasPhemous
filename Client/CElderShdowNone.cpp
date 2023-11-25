#include "pch.h"
#include "CElderShdowNone.h"


CElderShdowNone::CElderShdowNone()
{
}

CElderShdowNone::~CElderShdowNone()
{
}

void CElderShdowNone::finaltick(float _DT)
{
}

void CElderShdowNone::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Idle", false);
	}
	else
	{
		pAnimator->Play(L"Idle_L", false);
	}

}

void CElderShdowNone::Exit()
{
}


