#include "pch.h"
#include "CPenitentIdle.h"

#include "CCamera.h"

#include "CPenitent.h"

CPenitentIdle::CPenitentIdle()
{
	SetName(L"CPenitentIdle");
}

CPenitentIdle::~CPenitentIdle()
{
}

void CPenitentIdle::finaltick(float _DT)
{
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	bool bDir = GetOwnerObj->GetDir();


	// State º¯°æ

	// StartRun
	if ( (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT)) && KEY_NONE(KEY::RIGHT))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::STARTRRUN);
	}

	if ((KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT)) && KEY_NONE(KEY::LEFT))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::STARTRRUN);
	}

	if (KEY_TAP(KEY::DOWN) || KEY_PRESSED(KEY::DOWN))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCH);
	}

	if (KEY_TAP(KEY::Z) && pPenitent->GetPotionCount() > 0)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::HEALTHPOTION);
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

	if ((KEY_TAP(KEY::S) || KEY_PRESSED(KEY::S)) && KEY_PRESSED(KEY::UP) && !(KEY_TAP(KEY::F)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::UPWARDATTACK);
	}

	if (KEY_PRESSED(KEY::S))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CHARGING);
	}

	if (KEY_TAP(KEY::A))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::PARRY);
	}

	if (!pMovement->IsGround() && pMovement->GetVelocity().y > 0)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
	}



}

void CPenitentIdle::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	int iDir = GetOwnerObj->GetDir();
	// Vec2(60.f, -230.f);

	if (iDir)
	{
		pAnimator->Play(L"Idle", true);
	}
	else
	{
		pAnimator->Play(L"Idle_L", true);
	}
}

void CPenitentIdle::Exit()
{
}


