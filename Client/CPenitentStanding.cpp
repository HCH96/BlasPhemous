#include "pch.h"
#include "CPenitentStanding.h"

CPenitentStanding::CPenitentStanding()
{
}

CPenitentStanding::~CPenitentStanding()
{
}
void CPenitentStanding::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();


	if (KEY_PRESSED(KEY::LEFT) || KEY_PRESSED(KEY::RIGHT))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::STARTRRUN);
	}

	// Jump
	if (KEY_TAP(KEY::F))
	{
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMP);
	}

	if (KEY_TAP(KEY::D))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DODGE);
	}

	if (KEY_TAP(KEY::S) && !(KEY_TAP(KEY::F)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::ATTACK);
	}

	if (KEY_TAP(KEY::S) && KEY_PRESSED(KEY::UP) && !(KEY_TAP(KEY::F)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::UPWARDATTACK);
	}


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}
}

void CPenitentStanding::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(20.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pDustAnimator = GetOwnerObj->GetComponent<CAnimator>(L"Dust_Animator");
	pDustAnimator->SetLock(false);
	bool bDir = GetOwnerObj->GetDir();

	pMovement->SetVelocity(Vec2(0.f, 0.f));


	if (bDir)
	{
		pAnimator->Play(L"Standing", true);
		pDustAnimator->Play(L"StandingDust", true);

	}
	else
	{
		pAnimator->Play(L"Standing_L", true);
		pDustAnimator->Play(L"StandingDust_L", true);
	}
	
}

void CPenitentStanding::Exit()
{
	CAnimator* pDustAnimator = GetOwnerObj->GetComponent<CAnimator>(L"Dust_Animator");
	pDustAnimator->Stop();
}
