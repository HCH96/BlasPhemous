#include "pch.h"
#include "CPenitentJumpAttack.h"

CPenitentJumpAttack::CPenitentJumpAttack()
{
}

CPenitentJumpAttack::~CPenitentJumpAttack()
{
}


void CPenitentJumpAttack::finaltick(float _DT)
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CStateMachine* pOwnerSM = GetOwnerSM();
	

	Vec2 vVel = pMovement->GetVelocity();
	bool bDir = GetOwnerObj->GetDir();
	UINT iCurFrame = (UINT)pAnimator->GetCurFrame();
	bool isFinsh = false;
	

	// JumpATTSlash1 재생
	if (pAnimator->GetCurFrame() == 3)
	{
		if (bDir)
		{
			pEffector->PlayNoReset(L"JumpATTSlash1", false);
		}
		else
		{
			pEffector->PlayNoReset(L"JumpATTSlash1_L", false);
		}
	}

	// JumpATTSlash2 재생
	if (pAnimator->GetCurFrame() == 7)
	{
		if (bDir)
		{
			pEffector->PlayNoReset(L"JumpATTSlash2", false);
		}
		else
		{
			pEffector->PlayNoReset(L"JumpATTSlash2_L", false);
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
		pMovement->AddVelocity(Vec2(-150.f, 0.f));

	}

	if ((KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT)) && KEY_NONE(KEY::LEFT))
	{
		pMovement->AddVelocity(Vec2(150.f, 0.f));
	}

	// 상태 변화

	// 한 번 더 공격키를 눌렀다면 체크
	if (KEY_TAP(KEY::S))
	{
		pOwnerSM->EditDataToBlackboard(L"IsTapS", true);
	}

	if (iCurFrame == 7 && !*(bool*)(pOwnerSM->GetDataFromBlackboard(L"IsTapS")))
	{
		isFinsh = true;
	}


	// 방향 전환
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		if (bDir)
		{
			pAnimator->PlayFromFrame(L"JumpATT", iCurFrame, false);
		}
		else
		{
			pAnimator->PlayFromFrame(L"JumpATT_L", iCurFrame, false);
		}
	}

	if (isFinsh || pAnimator->IsFinish())
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

void CPenitentJumpAttack::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(20.f);
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();
	GetOwnerSM()->EditDataToBlackboard(L"IsTapS", false);

	if (bDir)
	{
		pAnimator->Play(L"JumpATT", false);
	}
	else
	{
		pAnimator->Play(L"JumpATT_L", false);
	}

	pEffector->Play(L"JumpATTSlash1", false);
	pEffector->Play(L"JumpATTSlash2", false);

	pEffector->Play(L"JumpATTSlash1_L", false);
	pEffector->Play(L"JumpATTSlash2_L", false);

	pEffector->Play(L"None", false);


}

void CPenitentJumpAttack::Exit()
{
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	pEffector->Play(L"None", false);
	GetOwnerSM()->EditDataToBlackboard(L"IsTapS", false);
}