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
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	Vec2 vVel = pMovement->GetVelocity();
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


	// 방향키 전환
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

	if ((KEY_TAP(KEY::F)) && GetOwnerSM()->GetCurState() != (UINT)PENITENT_STATE::STOPRUN && !(KEY_TAP(KEY::S)))
	{
		// JumpForward
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}

	if ((KEY_TAP(KEY::F)) && GetOwnerSM()->GetCurState() == (UINT)PENITENT_STATE::STOPRUN && !(KEY_TAP(KEY::S)))
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

	if (!pMovement->IsGround() && pMovement->GetVelocity().y > 0)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALLFORWARD);
	}
}

void CPenitentRun::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(20.f);
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CAnimator* pDustAnimator = GetOwnerObj->GetComponent<CAnimator>(L"Dust_Animator");
	bool bDir = GetOwnerObj->GetDir();
	pDustAnimator->SetLock(false);
	

	if (bDir)
	{
		pAnimator->Play(L"Run", true);
		pMovement->SetVelocity(Vec2(2.f, 0.f) * pMovement->GetInitSpeed());
		pDustAnimator->Play(L"RunDust", true);

	}
	else
	{
		pAnimator->Play(L"Run_L", true);
		pMovement->SetVelocity(Vec2(-2.f, 0.f) * pMovement->GetInitSpeed());
		pDustAnimator->Play(L"RunDust_L", true);
	}
}

void CPenitentRun::Exit()
{
	CAnimator* pDustAnimator = GetOwnerObj->GetComponent<CAnimator>(L"Dust_Animator");
	pDustAnimator->Stop();
}


