#include "pch.h"
#include "CShieldMaidenToIdle.h"

#include "CShieldMaiden.h"

CShieldMaidenToIdle::CShieldMaidenToIdle()
{
}

CShieldMaidenToIdle::~CShieldMaidenToIdle()
{
}

void CShieldMaidenToIdle::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::IDLE);
	}
}

void CShieldMaidenToIdle::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>(L"Shield_HitBox");
	CShieldMaiden* m_pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	m_pMon->SetStateBlock(true);


	bool bDir = pOwner->GetDir();
	pCollider->SetTime(0.f);
	if (bDir)
	{
		pAnimator->Play(L"ToIdle", false);
	}
	else
	{
		pAnimator->Play(L"ToIdle_L", false);
	}
}

void CShieldMaidenToIdle::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CShieldMaiden* pMon = dynamic_cast<CShieldMaiden*>(pOwner);

	CShieldMaiden* m_pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	m_pMon->SetStateBlock(false);
}

