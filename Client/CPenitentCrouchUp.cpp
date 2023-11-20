#include "pch.h"
#include "CPenitentCrouchUp.h"


CPenitentCrouchUp::CPenitentCrouchUp()
{
}

CPenitentCrouchUp::~CPenitentCrouchUp()
{
}

void CPenitentCrouchUp::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();

	// 방향 전환
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	// 상태 전환
	if (KEY_TAP(KEY::S))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::ATTACK);
	}

	if (KEY_TAP(KEY::D))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DODGE);
	}

	if ((KEY_PRESSED(KEY::DOWN)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCH);
	}

	// Jump
	if (KEY_TAP(KEY::F))
	{
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMP);
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}



}

void CPenitentCrouchUp::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"CrouchUp", false);
	}
	else
	{
		pAnimator->Play(L"CrouchUp_L", false);
	}

	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
	CCollider* pCol = pPenitent->GetComponent<CCollider>();
	pCol->SetScale(Vec2(40.f, 70.f));
	pCol->SetOffsetPos(Vec2(0.f, -35.f));

}

void CPenitentCrouchUp::Exit()
{
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
	CCollider* pCol = pPenitent->GetComponent<CCollider>();
	pCol->SetScale(Vec2(40.f, 120.f));
	pCol->SetOffsetPos(Vec2(0.f, -60.f));

}

