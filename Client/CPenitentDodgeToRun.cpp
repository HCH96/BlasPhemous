#include "pch.h"
#include "CPenitentDodgeToRun.h"

CPenitentDodgeToRun::CPenitentDodgeToRun()
	: m_bDir(true)
{
}

CPenitentDodgeToRun::~CPenitentDodgeToRun()
{
}

void CPenitentDodgeToRun::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	bool bDir = GetOwnerObj->GetDir();

	// 속도 변화
	if (m_bDir)
	{
		pMovement->SetVelocity(Vec2(300.f, pMovement->GetVelocity().y));
	}
	else
	{
		pMovement->SetVelocity(Vec2(-300.f, pMovement->GetVelocity().y));
	}


	// 상태 변화
	if (m_bDir != bDir)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::RUN);
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::RUN);
	}

	// JumpForward
	if (KEY_TAP(KEY::F))
	{
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}

	if (!pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALLFORWARD);
	}
	
}

void CPenitentDodgeToRun::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(20.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	m_bDir = GetOwnerObj->GetDir();

	if (m_bDir)
	{
		pAnimator->Play(L"DodgeToRun", false);
		pMovement->SetVelocity(Vec2(100.f, pMovement->GetVelocity().y) * pMovement->GetInitSpeed());
		//pMovement->AddForce(Vec2(100.f, 0.f));
	}
	else
	{
		pAnimator->Play(L"DodgeToRun_L", false);
		pMovement->SetVelocity(Vec2(-100.f, pMovement->GetVelocity().y) * pMovement->GetInitSpeed());
		//pMovement->AddForce(Vec2(100.f, 0.f));
	}
}

void CPenitentDodgeToRun::Exit()
{
}
