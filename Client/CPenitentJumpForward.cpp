#include "pch.h"
#include "CPenitentJumpForward.h"

CPenitentJumpForward::CPenitentJumpForward()
{
	SetName(L"CPenitentJumpForward");
}

CPenitentJumpForward::~CPenitentJumpForward()
{
}


void CPenitentJumpForward::finaltick(float _DT)
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();

	Vec2 vVel = pMovement->GetVelocity();
	bool bDir = GetOwnerObj->GetDir();

	// 속도 변화

	if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
	{
		pMovement->SetVelocity(Vec2(0.f, vVel.y));
	}

	if ((KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT)) && (KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT)))
	{
		pMovement->SetVelocity(Vec2(0.f, vVel.y));
	}

	if ((KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT)) && KEY_NONE(KEY::RIGHT))
	{
		pMovement->AddVelocity(Vec2(-200.f, 0.f));

	}

	if ((KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT)) && KEY_NONE(KEY::LEFT))
	{
		pMovement->AddVelocity(Vec2(200.f, 0.f));
	}


	// 상태 변화

	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		Enter();
	}

	if (vVel.y > 0 && pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARDFALL);
	}

	if (pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}
	
}

void CPenitentJumpForward::Enter()
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	Vec2 vVel = pMovement->GetVelocity();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"JumpForward", false);
	}
	else
	{
		pAnimator->Play(L"JumpForward_L", false);
	}
}

void CPenitentJumpForward::Exit()
{
}