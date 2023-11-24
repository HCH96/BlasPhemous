#include "pch.h"
#include "CPenitentStopRun.h"

CPenitentStopRun::CPenitentStopRun()
{
	SetName(L"CPenitentStopRun");
}

CPenitentStopRun::~CPenitentStopRun()
{
}


void CPenitentStopRun::finaltick(float _DT)
{
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	// 방향이 바뀐 경우
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::STARTRRUN);
	}

	if ((KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT)) && KEY_NONE(KEY::RIGHT))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::STARTRRUN);
	}

	if ((KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT)) && KEY_NONE(KEY::LEFT))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::STARTRRUN);
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

	if ((KEY_TAP(KEY::F)) && !(KEY_TAP(KEY::S)))
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
	if ((KEY_TAP(KEY::S) || KEY_PRESSED(KEY::S)) && KEY_PRESSED(KEY::UP) && !(KEY_TAP(KEY::F)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::UPWARDATTACK);
	}


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	if (!pMovement->IsGround() && pMovement->GetVelocity().y > 0)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
	}

}

void CPenitentStopRun::Enter()
{
	//CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CAnimator* pDustAnimator = GetOwnerObj->GetComponent<CAnimator>(L"Dust_Animator");
	bool bDir = GetOwnerObj->GetDir();
	pDustAnimator->SetLock(false);

	
	if (bDir)
	{
		pAnimator->Play(L"Stop_Run", true);
		pDustAnimator->Play(L"StopRun", false);
	}
	else
	{
		pAnimator->Play(L"Stop_Run_L", true);
		pDustAnimator->Play(L"StopRun_L", false);
	}

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_RUNSTOP_STONE", L"sound\\Object\\Player\\PENITENT_RUNSTOP_STONE.wav");
	pSound->SetVolume(100.f);
	pSound->Play();
}

void CPenitentStopRun::Exit()
{
}


