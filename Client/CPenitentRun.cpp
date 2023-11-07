#include "pch.h"
#include "CPenitentRun.h"

CPenitentRun::CPenitentRun()
{
	SetName(L"CPenitentRun");
}

CPenitentRun::~CPenitentRun()
{
}

void CPenitentRun::finaltick(float _DT)
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	Vec2 vVel = pMovement->GetVelocity();
	bool bDir = GetOwnerObj->GetDir();

	// 속도 변화
	if (bDir)
	{
		pMovement->AddForce(Vec2(300.f, 0.f));
	}
	else
	{
		pMovement->AddForce(Vec2(-300.f, 0.f));
	}


	// 방향키 전환
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		pMovement->SetVelocity({ -vVel.x, vVel.y });
		Enter();
	}

	// change state
	if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::STOPRUN);
	}

	if (KEY_PRESSED(KEY::RIGHT) && KEY_PRESSED(KEY::LEFT))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::STOPRUN);
	}

	if (KEY_TAP(KEY::DOWN) || KEY_PRESSED(KEY::DOWN))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCH);
	}

	if (KEY_TAP(KEY::Z))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::HEALTHPOTION);
	}

	if (KEY_TAP(KEY::D))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DODGE);
	}

	if ((KEY_TAP(KEY::F)) && GetOwnerSM()->GetCurState() != (UINT)PENITENT_STATE::STOPRUN && !(KEY_TAP(KEY::S)))
	{
		// JumpForward
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}

	if ((KEY_TAP(KEY::F)) && GetOwnerSM()->GetCurState() == (UINT)PENITENT_STATE::STOPRUN && !(KEY_TAP(KEY::S)))
	{
		// JumpForward
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMP);
	}

	if (KEY_TAP(KEY::S) && !(KEY_TAP(KEY::F)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::ATTACK);
	}
}

void CPenitentRun::Enter()
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Run", true);

		pMovement->SetVelocity(Vec2(2.f, 0.f) * pMovement->GetInitSpeed());

	}
	else
	{
		pAnimator->Play(L"Run_L", true);
		pMovement->SetVelocity(Vec2(-2.f, 0.f) * pMovement->GetInitSpeed());
		
	}
}

void CPenitentRun::Exit()
{
}


