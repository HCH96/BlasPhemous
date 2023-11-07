#include "pch.h"
#include "CPenitentUpwardATTJump.h"


CPenitentUpwardATTJump::CPenitentUpwardATTJump()
{
}

CPenitentUpwardATTJump::~CPenitentUpwardATTJump()
{
}

void CPenitentUpwardATTJump::finaltick(float _DT)
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	
	Vec2 vVel = pMovement->GetVelocity();

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

	if (pAnimator->IsFinish())
	{
		if (vVel.x == 0)
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
		else
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALLFORWARD);
	}

	if (pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}


}

void CPenitentUpwardATTJump::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"UpwardAttck_Jump", false);
	}
	else
	{
		pAnimator->Play(L"UpwardAttck_Jump_L", false);
	}
}

void CPenitentUpwardATTJump::Exit()
{
}
