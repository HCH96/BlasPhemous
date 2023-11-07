#include "pch.h"
#include "CPenitentJump.h"

CPenitentJump::CPenitentJump()
{
	SetName(L"CPenitentJump");
}

CPenitentJump::~CPenitentJump()
{
}


void CPenitentJump::finaltick(float _DT)
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

	if (vVel.y > 0)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
	}

	if ((KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT)) && KEY_NONE(KEY::RIGHT) && GetOwnerSM()->GetCurState() != (UINT)PENITENT_STATE::FALL)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}

	if ((KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT)) && GetOwnerSM()->GetCurState() != (UINT)PENITENT_STATE::FALL)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}


	if (KEY_TAP(KEY::S))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPATT);
	}

	if (KEY_TAP(KEY::S) && KEY_PRESSED(KEY::UP))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::UPWARDATTACKJUMP);
	}

	



	if (pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	
}

void CPenitentJump::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();


	if (bDir)
	{
		pAnimator->Play(L"Jump", true);
	}
	else
	{
		pAnimator->Play(L"Jump_L", true);
	}
}

void CPenitentJump::Exit()
{
}

