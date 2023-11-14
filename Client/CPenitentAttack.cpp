#include "pch.h"
#include "CPenitentAttack.h"


CPenitentAttack::CPenitentAttack()
{
}

CPenitentAttack::~CPenitentAttack()
{
}

void CPenitentAttack::finaltick(float _DT)
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CStateMachine* pOwnerSM = GetOwnerSM();

	
	

	bool isFinsh = false;
	UINT iCurFrame = (UINT)pAnimator->GetCurFrame();
	UINT iEffectFrame = (UINT)pEffector->GetCurFrame();

	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");
	


	// Attack 1 ( 0 Frame ~ 7 Frame )
	if (iCurFrame >= 0 && iCurFrame <= 8)
	{
		if (iCurFrame >= 3 && iCurFrame < 8)
		{
			if (KEY_TAP(KEY::S))
			{
				pOwnerSM->EditDataToBlackboard(L"IsTapS", true);
			}
		}

		// 4~7 Frame 동안 공격을 시도하지 않았다면 종료
		if (iCurFrame == 8 && !*(bool*)(pOwnerSM->GetDataFromBlackboard(L"IsTapS")))
		{
			isFinsh = true;
		}
	}


	// Attack 2 ( 8 Frame ~ 14 Frame )
	if (iCurFrame > 8 && iCurFrame <= 14)
	{
		if (iCurFrame == 9)
		{
			pOwnerSM->EditDataToBlackboard(L"IsTapS", false);
		}
		
		if (iCurFrame >= 9 && iCurFrame < 14)
		{
			if (KEY_TAP(KEY::S))
			{
				pOwnerSM->EditDataToBlackboard(L"IsTapS", true);
			}
		}
		// 11~13 Frame 동안 공격을 시도하지 않았다면 종료
		if (iCurFrame == 14 && !*(bool*)(pOwnerSM->GetDataFromBlackboard(L"IsTapS")))
		{
			isFinsh = true;
		}
	}

	// Attack 3
	if (iCurFrame > 14 && iCurFrame <= 27)
	{
		if (iCurFrame == 14)
		{
			pOwnerSM->EditDataToBlackboard(L"IsTapS", false);
		}

		// 모든 프레임을 출력한 뒤 종료
		if (iCurFrame == 27)
		{
			isFinsh = true;
		}
	}

	if (iCurFrame == 4 ||iCurFrame == 11 || iCurFrame == 18)
	{
		pHitBox->On();
	}


	if (isFinsh)
	{
		pOwnerSM->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	if (KEY_TAP(KEY::D))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DODGE);
	}

	if (!pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
	}


}

void CPenitentAttack::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");
	pHitBox->SetScale(Vec2(150.f, 110.f));
	
	pHitBox->SetTime(0.15f);


	
	m_bDir = GetOwnerObj->GetDir();
	GetOwnerSM()->EditDataToBlackboard(L"IsTapS", false);

	if (m_bDir)
	{
		pAnimator->Play(L"Attack", true);
		pEffector->Play(L"AttackSlash", false);
		pMovement->SetVelocity(Vec2(0.f, 0.f));
		pHitBox->SetOffsetPos(Vec2(100.f, -70.f));
	}
	else
	{
		pAnimator->Play(L"Attack_L", true);
		pEffector->Play(L"AttackSlash_L", false);
		pMovement->SetVelocity(Vec2(0.f, 0.f));
		pHitBox->SetOffsetPos(Vec2(-100.f, -70.f));
	}

}

void CPenitentAttack::Exit()
{
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	
	pEffector->Play(L"None", false);
	GetOwnerSM()->EditDataToBlackboard(L"IsTapS", false);
}

