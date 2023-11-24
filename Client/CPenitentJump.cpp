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
		pMovement->AddVelocity(Vec2(-150.f, 0.f));

	}

	if ((KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT)) && KEY_NONE(KEY::LEFT))
	{
		pMovement->AddVelocity(Vec2(150.f, 0.f));
	}

	

	// 상태 변화

	if ((KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT)) && KEY_NONE(KEY::RIGHT))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}

	if ((KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}

	if (vVel.y > 0 && vVel.x == 0)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
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
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_JUMP_FALL_STONE", L"sound\\Object\\Player\\PENITENT_JUMP_FALL_STONE.wav");
		pSound->SetVolume(100.f);
		pSound->Play();

		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	
}

void CPenitentJump::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	CAnimator* pDustAnimator = GetOwnerObj->GetComponent<CAnimator>(L"Dust_Animator");
	pDustAnimator->SetLock(true);
	pDustAnimator->SetTmpPos(GetOwnerObj->GetPos());

	if (bDir)
	{
		pAnimator->Play(L"Jump", true);
		pDustAnimator->Play(L"Jumping_dust", false);
	}
	else
	{
		pAnimator->Play(L"Jump_L", true);
		pDustAnimator->Play(L"Jumping_dust_L", false);
	}

	if (GetOwnerSM()->GetPrevState() != (UINT)PENITENT_STATE::JUMPFORWARD)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_JUMP", L"sound\\Object\\Player\\PENITENT_JUMP.wav");
		pSound->SetVolume(100.f);
		pSound->Play();
	}


}

void CPenitentJump::Exit()
{
}

