#include "pch.h"
#include "CShieldMaidenParryReaction.h"

#include "CShieldMaiden.h"

CShieldMaidenParryReaction::CShieldMaidenParryReaction()
{
}

CShieldMaidenParryReaction::~CShieldMaidenParryReaction()
{
}
void CShieldMaidenParryReaction::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::IDLE);
	}
}

void CShieldMaidenParryReaction::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>(L"Shield_HitBox");
	CShieldMaiden* m_pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	m_pMon->SetStateBlock(false);

	bool bDir = pOwner->GetDir();
	pCollider->SetTime(0.f);
	if (bDir)
	{
		pAnimator->Play(L"ParryReaction", false);
	}
	else
	{
		pAnimator->Play(L"ParryReaction_L", false);
	}
}

void CShieldMaidenParryReaction::Exit()
{
}


