#include "pch.h"
#include "CShieldMaidenAttack.h"

#include "CLevelMgr.h"
#include "CPenitent.h"

#include "CShieldMaiden.h"

CShieldMaidenAttack::CShieldMaidenAttack()
{
}

CShieldMaidenAttack::~CShieldMaidenAttack()
{
}

void CShieldMaidenAttack::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	bool bDir = pOwner->GetDir();

	CCollider* pHitBox = pOwner->GetComponent<CCollider>(L"Shield_HitBox");
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();

	if (pAnimator->GetCurFrame() == 5)
	{
		pHitBox->On();
	}

	if (pAnimator->GetCurFrame() == 7)
	{
		if (pPenitent->GetParry() == 2)
		{
			GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::PARRYREACTION);
		}
	}


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::IDLE);
	}

}

void CShieldMaidenAttack::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pHitBox = pOwner->GetComponent<CCollider>(L"Shield_HitBox");
	bool bDir = pOwner->GetDir();
	pHitBox->SetTime(0.5);

	CShieldMaiden* m_pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	m_pMon->SetStateBlock(false);

	if (bDir)
	{
		pAnimator->Play(L"Attack", false);
		pHitBox->SetOffsetPos(Vec2(70.f, -50.f));
	}
	else
	{
		pAnimator->Play(L"Attack_L", false);
		pHitBox->SetOffsetPos(Vec2(-70.f, -50.f));
	}

}

void CShieldMaidenAttack::Exit()
{
}

