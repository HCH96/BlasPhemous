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
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
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

	if (KEY_TAP(KEY::DOWN) || KEY_PRESSED(KEY::DOWN))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCH);
	}

	if (KEY_TAP(KEY::Z) && pPenitent->GetPotionCount() > 0)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::HEALTHPOTION);
	}

	if (KEY_TAP(KEY::D))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DODGE);
	}
	if (KEY_TAP(KEY::Z) && pPenitent->GetPotionCount() > 0)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::HEALTHPOTION);
	}

	if ((KEY_TAP(KEY::F)) && GetOwnerSM()->GetCurState() != (UINT)PENITENT_STATE::IDLE && !(KEY_TAP(KEY::S)))
	{
		// JumpForward
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}

	if ((KEY_TAP(KEY::F)) && GetOwnerSM()->GetCurState() == (UINT)PENITENT_STATE::IDLE && !(KEY_TAP(KEY::S)))
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
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::RUN);
	}

	if (!pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALLFORWARD);
	}
}

void CPenitentStartRun::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(20.f);
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

