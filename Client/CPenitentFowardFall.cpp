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
		pMovement->AddVelocity(Vec2(-150.f, 0.f));

	}

	if ((KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT)) && KEY_NONE(KEY::LEFT))
	{
		pMovement->AddVelocity(Vec2(150.f, 0.f));
	}


	// 상태 변화
	// 방향 전환
	bool bDir = GetOwnerObj->GetDir();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	UINT iCurFrame = (UINT)pAnimator->GetCurFrame();

	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		if (bDir)
		{
			pAnimator->PlayFromFrame(L"JumpForwardFall", iCurFrame, false);
		}
		else
		{
			pAnimator->PlayFromFrame(L"JumpForwardFall_L", iCurFrame, false);
		}
	}

	// Fall
	if (pMovement->GetVelocity().x == 0.f)
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

		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::STANDING);
	}
	
}

void CPenitentFowardFall::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(20.f);
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();
	Vec2 vVel = pMovement->GetVelocity();

	if (bDir)
	{
		pAnimator->Play(L"JumpForwardFall", true);
	}
	else
	{
		pAnimator->Play(L"JumpForwardFall_L", true);
	}
}

void CPenitentFowardFall::Exit()
{
}



