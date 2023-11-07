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
		pMovement->SetVelocity(Vec2(300.f, 0.f));
	}
	else
	{
		pMovement->SetVelocity(Vec2(-300.f, 0.f));
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

}

void CPenitentDodgeToRun::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	m_bDir = GetOwnerObj->GetDir();

	if (m_bDir)
	{
		pAnimator->Play(L"DodgeToRun", false);
		pMovement->SetVelocity(Vec2(100.f, 0.f) * pMovement->GetInitSpeed());
		//pMovement->AddForce(Vec2(100.f, 0.f));
	}
	else
	{
		pAnimator->Play(L"DodgeToRun_L", false);
		pMovement->SetVelocity(Vec2(-100.f, 0.f) * pMovement->GetInitSpeed());
		//pMovement->AddForce(Vec2(100.f, 0.f));
	}
}

void CPenitentDodgeToRun::Exit()
{
}
