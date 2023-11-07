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
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CStateMachine* pOwnerSM = GetOwnerSM();
	Vec2 vVel = pMovement->GetVelocity();

	int iCurFrame = pAnimator->GetCurFrame();
	bool isFinsh = false;

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

	// 한 번 더 공격키를 눌렀다면 체크
	if (KEY_TAP(KEY::S))
	{
		pOwnerSM->EditDataToBlackboard(L"IsTapS", true);
	}

	if (iCurFrame == 4 && !*(bool*)(pOwnerSM->GetDataFromBlackboard(L"IsTapS")))
	{
		isFinsh = true;
	}




	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		Enter();
	}

	if (isFinsh)
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
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
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

}

void CPenitentJumpAttack::Exit()
{
	GetOwnerSM()->EditDataToBlackboard(L"IsTapS", false);
}