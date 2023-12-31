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

	
	GetOwnerObj->SetDir(m_bDir);

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
		if (m_iPrevFrame == 3)
		{
			CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_SLASH_AIR_1", L"sound\\Object\\Player\\PENITENT_SLASH_AIR_1.wav");
			pSound->Play();
		}


		if (m_iPrevFrame == 10)
		{
			CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_SLASH_AIR_2", L"sound\\Object\\Player\\PENITENT_SLASH_AIR_2.wav");
			pSound->Play();
		}

		if (m_iPrevFrame == 17)
		{
			CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_SLASH_AIR_3", L"sound\\Object\\Player\\PENITENT_SLASH_AIR_3.wav");
			pSound->Play();
		}

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
	if (KEY_TAP(KEY::A))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::PARRY);
	}


	if (!pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALL);
	}


	m_iPrevFrame = iCurFrame;

}

void CPenitentAttack::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");


	pHitBox->SetScale(Vec2(150.f, 110.f));
	pHitBox->SetOffsetPos(Vec2(100.f, -70.f));
	pHitBox->SetTime(0.15f);

	m_iPrevFrame = 0;
	
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
	if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT))
	{
		GetOwnerObj->SetDir(false);
	}

	if (KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
	{
		GetOwnerObj->SetDir(true);
	}


	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	
	pEffector->Play(L"None", false);
	GetOwnerSM()->EditDataToBlackboard(L"IsTapS", false);
}

