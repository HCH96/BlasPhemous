#include "pch.h"
#include "CShieldMaidenStun.h"

#include "CShieldMaiden.h"

CShieldMaidenStun::CShieldMaidenStun()
	: m_fAcc(0.f)
	, m_fDuration(3.f)
{
}

CShieldMaidenStun::~CShieldMaidenStun()
{
}

void CShieldMaidenStun::finaltick(float _DT)
{
	m_fAcc += _DT;

	if (m_fDuration < m_fAcc)
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::IDLE);
	}

}

void CShieldMaidenStun::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>(L"Shield_HitBox");
	CShieldMaiden* m_pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	m_pMon->SetStateBlock(false);
	m_fAcc = 0.f;

	bool bDir = pOwner->GetDir();
	pCollider->SetTime(0.f);
	if (bDir)
	{
		pAnimator->Play(L"Stun", false);
	}
	else
	{
		pAnimator->Play(L"Stun_L", false);
	}

}

void CShieldMaidenStun::Exit()
{
}

