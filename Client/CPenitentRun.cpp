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

	// �ӵ� ��ȭ
	if (bDir)
	{
		pMovement->AddForce(Vec2(300.f, 0.f));
	}
	else
	{
		pMovement->AddForce(Vec2(-300.f, 0.f));
	}


	// ����Ű ��ȯ
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

	if ((KEY_TAP(KEY::F)) && GetOwnerSM()->GetCurState() != (UINT)PENITENT_STATE::STOPRUN)
	{
		// JumpForward
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}

	if ((KEY_TAP(KEY::F)) && GetOwnerSM()->GetCurState() == (UINT)PENITENT_STATE::STOPRUN)
	{
		// JumpForward
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMP);
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
	}
	else
	{
		pAnimator->Play(L"Run_L", true);
	}
}

void CPenitentRun::Exit()
{
}


