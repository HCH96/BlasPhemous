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
	CObj* pOwner = GetOwnerObj;
	

}

void CElderIntro::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	pMovement->SetGround(true);
	pMovement->SetMaxDown(0.f);

	bool bDir = pOwner->GetDir();



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
	CObj* pOwner = GetOwnerObj;

	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	pMovement->SetGround(false);
	pMovement->SetMaxDown(1000.f);

}

