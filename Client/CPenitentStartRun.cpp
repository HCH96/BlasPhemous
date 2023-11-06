#include "pch.h"
#include "CPenitentStartRun.h"


CPenitentStartRun::CPenitentStartRun()
{
	SetName(L"CPenitentStartRun");
}

CPenitentStartRun::~CPenitentStartRun()
{
}


void CPenitentStartRun::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
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


	// 상태 변화

	// 방향이 바뀐 경우
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	if ((KEY_TAP(KEY::F)) && GetOwnerSM()->GetCurState() != (UINT)PENITENT_STATE::IDLE)
	{
		// JumpForward
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}

	if ((KEY_TAP(KEY::F)) && GetOwnerSM()->GetCurState() == (UINT)PENITENT_STATE::IDLE)
	{
		// JumpForward
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMP);
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::RUN);
	}

}

void CPenitentStartRun::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Start_Run", false);
		pMovement->SetVelocity(Vec2(1.f, 0.f) * pMovement->GetInitSpeed());
	}
	else
	{
		pAnimator->Play(L"Start_Run_L", false);
		pMovement->SetVelocity(Vec2(-1.f, 0.f) * pMovement->GetInitSpeed());
	}
}

void CPenitentStartRun::Exit()
{
}

