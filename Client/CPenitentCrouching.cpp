#include "pch.h"
#include "CPenitentCrouching.h"

CPenitentCrouching::CPenitentCrouching()
{
}

CPenitentCrouching::~CPenitentCrouching()
{
}

void CPenitentCrouching::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	bool bDir = GetOwnerObj->GetDir();
	
	if (GetOwnerObj->GetDir() != GetOwnerObj->GetPrevDir())
	{
		Enter();
	}

	if (!(KEY_PRESSED(KEY::DOWN)))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHUP);
	}

	if (KEY_TAP(KEY::S))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHATT);
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

	if (!pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
	}

}

void CPenitentCrouching::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Crouching", false);
	}
	else
	{
		pAnimator->Play(L"Crouching_L", false);
	}

	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
	CCollider* pCol = pPenitent->GetComponent<CCollider>();
	pCol->SetScale(Vec2(40.f, 70.f));
	pCol->SetOffsetPos(Vec2(0.f, -35.f));
}

void CPenitentCrouching::Exit()
{
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
	CCollider* pCol = pPenitent->GetComponent<CCollider>();
	pCol->SetScale(Vec2(40.f, 110.f));
	pCol->SetOffsetPos(Vec2(0.f, -60.f));
}

