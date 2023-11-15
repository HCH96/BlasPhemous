#include "pch.h"
#include "CPenitentHangOn.h"

CPenitentHangOn::CPenitentHangOn()
{
}

CPenitentHangOn::~CPenitentHangOn()
{
}

void CPenitentHangOn::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CMovement* pMovement = pOwner->GetComponent<CMovement>();



	if (KEY_TAP(KEY::UP))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CLIMB);
	}

}

void CPenitentHangOn::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	pMovement->SetVelocity(Vec2(0.f, 0.f));
	pMovement->UseGravity(false);
	
	int iDir = pOwner->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"HangOn", false);
	}
	else
	{
		pAnimator->Play(L"HangOn_L", false);
	}

}

void CPenitentHangOn::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	pMovement->UseGravity(true);
	pMovement->SetGround(true);
}

