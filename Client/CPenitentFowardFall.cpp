#include "pch.h"
#include "CPenitentFowardFall.h"

CPenitentFowardFall::CPenitentFowardFall()
{
	SetName(L"CPenitentFowardFall");
}

CPenitentFowardFall::~CPenitentFowardFall()
{
}

void CPenitentFowardFall::finaltick(float _DT)
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
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

	if (pMovement->GetVelocity().x == 0.f)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
	}

	if (pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	
}

void CPenitentFowardFall::Enter()
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();
	Vec2 vVel = pMovement->GetVelocity();

	if (bDir)
	{
		pAnimator->Play(L"JumpForwardFall", true);
		//pMovement->SetVelocity(Vec2(1.f * pMovement->GetInitSpeed(), vVel.y));
	}
	else
	{
		pAnimator->Play(L"JumpForwardFall_L", true);
		//pMovement->SetVelocity(Vec2(-1.f * pMovement->GetInitSpeed(), vVel.y));
	}
}

void CPenitentFowardFall::Exit()
{
}



