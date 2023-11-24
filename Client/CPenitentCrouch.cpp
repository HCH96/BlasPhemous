#include "pch.h"
#include "CPenitentCrouch.h"

CPenitentCrouch::CPenitentCrouch()
{
}

CPenitentCrouch::~CPenitentCrouch()
{
}


void CPenitentCrouch::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	bool bDir = GetOwnerObj->GetDir();
	UINT iCurFrame = (UINT)pAnimator->GetCurFrame();


	// 방향 전환
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		if (bDir)
		{
			pAnimator->PlayFromFrame(L"Crouch", iCurFrame, false);
		}
		else
		{
			pAnimator->PlayFromFrame(L"Crouch_L", iCurFrame, false);
		}
	}

	// 상태 전환
	if ( (KEY_PRESSED(KEY::S) || KEY_TAP(KEY::S)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHATT);
	}

	if (KEY_TAP(KEY::D))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DODGE);
	}
	
	if (!(KEY_PRESSED(KEY::DOWN)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHUP);
	}

	if (KEY_TAP(KEY::F) && KEY_PRESSED(KEY::DOWN))
	{
		if (CLevelMgr::GetInst()->GetCurLeveli() == (UINT)LEVEL_TYPE::STAGE01_2 || CLevelMgr::GetInst()->GetCurLeveli() == (UINT)LEVEL_TYPE::STAGE02_1)
		{
			pMovement->SetGround(false);
			pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, 0.f));

			dynamic_cast<CPenitent*>(GetOwnerObj)->SetDownPlatform(true);


			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
		}

		
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHING);
	}


}

void CPenitentCrouch::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
	CCollider* pCol = pPenitent->GetComponent<CCollider>();
	pCol->SetScale(Vec2(40.f, 70.f));
	pCol->SetOffsetPos(Vec2(0.f, -35.f));

	if (bDir)
	{
		pAnimator->Play(L"Crouch", false);
	}
	else
	{
		pAnimator->Play(L"Crouch_L", false);
	}
}

void CPenitentCrouch::Exit()
{

	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
	CCollider* pCol = pPenitent->GetComponent<CCollider>();
	pCol->SetScale(Vec2(40.f, 110.f));
	pCol->SetOffsetPos(Vec2(0.f, -60.f));
}

