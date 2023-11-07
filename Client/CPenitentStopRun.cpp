#include "pch.h"
#include "CPenitentStopRun.h"

CPenitentStopRun::CPenitentStopRun()
{
	SetName(L"CPenitentStopRun");
}

CPenitentStopRun::~CPenitentStopRun()
{
}


void CPenitentStopRun::finaltick(float _DT)
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	// 방향이 바뀐 경우
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::STARTRRUN);
	}

	if ((KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT)) && KEY_NONE(KEY::RIGHT))
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

	if (KEY_TAP(KEY::Z))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::HEALTHPOTION);
	}

	if (KEY_TAP(KEY::D))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DODGE);
	}


	if ((KEY_TAP(KEY::F)) && !(KEY_TAP(KEY::S)))
	{
		// Jump
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMP);
	}

	if (KEY_TAP(KEY::S) && !(KEY_TAP(KEY::F)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::ATTACK);
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}


}

void CPenitentStopRun::Enter()
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Stop_Run", true);
	}
	else
	{
		pAnimator->Play(L"Stop_Run_L", true);
	}
}

void CPenitentStopRun::Exit()
{
}


