#include "pch.h"
#include "CPenitentUpwardATTJump.h"


CPenitentUpwardATTJump::CPenitentUpwardATTJump()
{
}

CPenitentUpwardATTJump::~CPenitentUpwardATTJump()
{
}

void CPenitentUpwardATTJump::finaltick(float _DT)
{
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();

	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");
	UINT iCurFrame = (UINT)pAnimator->GetCurFrame();
	bool bDir = GetOwnerObj->GetDir();
	Vec2 vVel = pMovement->GetVelocity();


	if (pAnimator->GetCurFrame() == 4)
	{
		pHitBox->On();

		if (bDir)
		{
			pEffector->PlayNoReset(L"UpwardATTJump", false);
		}
		else
		{
			pEffector->PlayNoReset(L"UpwardATTJump_L", false);
		}
	}



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

	// 방향 전환
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		if (bDir)
		{
			pAnimator->PlayFromFrame(L"UpwardAttck_Jump", iCurFrame, false);
		}
		else
		{
			pAnimator->PlayFromFrame(L"UpwardAttck_Jump_L", iCurFrame, false);
		}
	}

	if (pAnimator->IsFinish())
	{
		if (vVel.x == 0)
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
		else
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALLFORWARD);
	}

	if (pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}


}

void CPenitentUpwardATTJump::Enter()
{
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");
	pHitBox->SetScale(Vec2(150.f, 150.f));
	pHitBox->SetOffsetPos(Vec2(0.f, -180.f));
	pHitBox->SetTime(0.09f);
	bool bDir = GetOwnerObj->GetDir();
	
	if (bDir)
	{
		pAnimator->Play(L"UpwardAttck_Jump", false);
	}
	else
	{
		pAnimator->Play(L"UpwardAttck_Jump_L", false);
	}

	pEffector->Play(L"UpwardATTJump", false);
	pEffector->Play(L"UpwardATTJump_L", false);

	pEffector->Play(L"None", false);
}

void CPenitentUpwardATTJump::Exit()
{
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	pEffector->Play(L"None", false);
}
