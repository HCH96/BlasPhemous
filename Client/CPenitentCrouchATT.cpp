#include "pch.h"
#include "CPenitentCrouchATT.h"

CPenitentCrouchATT::CPenitentCrouchATT()
	: m_bDir(true)
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
		if (m_bDir)
		{
			pEffector->PlayNoReset(L"CrouchAttackSlash", false);
			pHitBox->SetScale(Vec2(120.f, 80.f));
			pHitBox->SetOffsetPos(Vec2(60.f, -20.f));
			pHitBox->SetTime(0.12f);
		}
		else
		{
			pEffector->PlayNoReset(L"CrouchAttackSlash_L", false);
			pHitBox->SetScale(Vec2(-120.f, 80.f));
			pHitBox->SetOffsetPos(Vec2(-60.f, -20.f));
			pHitBox->SetTime(0.12f);
		}
	}


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::CROUCHING);
	}
}

void CPenitentCrouchATT::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	bool bDir = GetOwnerObj->GetDir();

	if (bDir)
	{
		m_bDir = bDir;
		pAnimator->Play(L"CrouchATT", false);
		
	}
	else
	{
		m_bDir = bDir;
		pAnimator->Play(L"CrouchATT_L", false);
	}

	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	pEffector->Play(L"CrouchAttackSlash", false);
	pEffector->Play(L"CrouchAttackSlash_L", false);
	pEffector->Play(L"None", false);
}

void CPenitentCrouchATT::Exit()
{
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	pEffector->Play(L"None", false);
}
