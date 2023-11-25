#include "pch.h"
#include "CElderIntro.h"

CElderIntro::CElderIntro()
{
}

CElderIntro::~CElderIntro()
{
}

void CElderIntro::finaltick(float _DT)
{
}

void CElderIntro::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	bool bDir = pOwner->GetDir();


	pCollider->On();


	if (bDir)
	{
		pAnimator->Play(L"Idle", true);
	}
	else
	{
		pAnimator->Play(L"Idle_L", true);
	}

}

void CElderIntro::Exit()
{
}

