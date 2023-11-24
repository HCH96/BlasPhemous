#include "pch.h"
#include "CPenitentCrouchATT.h"

CPenitentCrouchATT::CPenitentCrouchATT()
	: m_bDir(true)
	, m_iPrevFrame(0)
{
}

CPenitentCrouchATT::~CPenitentCrouchATT()
{
}

void CPenitentCrouchATT::finaltick(float _DT)
{
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bCurDir = GetOwnerObj->GetDir();

	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");



	if (pAnimator->GetCurFrame() == 6)
	{
		if (m_iPrevFrame == 5)
		{
			CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_SLASH_AIR_1", L"sound\\Object\\Player\\PENITENT_SLASH_AIR_1.wav");
			pSound->Play();
		}

		if (m_bDir)
		{
			pEffector->PlayNoReset(L"CrouchAttackSlash", false);
			
		}
		else
		{
			pEffector->PlayNoReset(L"CrouchAttackSlash_L", false);
		}
		pHitBox->On();
	}





	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHING);
	}

	m_iPrevFrame = pAnimator->GetCurFrame();

}

void CPenitentCrouchATT::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");
	pHitBox->SetScale(Vec2(120.f, 80.f));
	pHitBox->SetOffsetPos(Vec2(60.f, -20.f));
	pHitBox->SetTime(0.12f);
	m_iPrevFrame = 0;

	m_bDir = GetOwnerObj->GetDir();

	if (m_bDir)
	{
		
		pAnimator->Play(L"CrouchATT", false);
		pHitBox->SetOffsetPos(Vec2(60.f, -20.f));
		
	}
	else
	{
		pAnimator->Play(L"CrouchATT_L", false);
		pHitBox->SetOffsetPos(Vec2(-60.f, -20.f));
	}

	CCollider* pCol = GetOwnerObj->GetComponent<CCollider>();
	pCol->SetScale(Vec2(40.f, 70.f));
	pCol->SetOffsetPos(Vec2(0.f, -35.f));

	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	pEffector->Play(L"CrouchAttackSlash", false);
	pEffector->Play(L"CrouchAttackSlash_L", false);
	pEffector->Play(L"None", false);
}

void CPenitentCrouchATT::Exit()
{
	CCollider* pCol = GetOwnerObj->GetComponent<CCollider>();
	pCol->SetScale(Vec2(40.f, 110.f));
	pCol->SetOffsetPos(Vec2(0.f, -60.f));

	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	pEffector->Play(L"None", false);
}
