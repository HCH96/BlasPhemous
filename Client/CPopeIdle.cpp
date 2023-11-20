#include "pch.h"
#include "CPopeIdle.h"

CPopeIdle::CPopeIdle()
	: m_fDuration(0.f)
	, m_fAcc(0.f)
	, m_pTarget(nullptr)
{
}

CPopeIdle::~CPopeIdle()
{
}

void CPopeIdle::finaltick(float _DT)
{
	m_fAcc += _DT;

	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();


	if (m_fAcc > m_fDuration && pAnimator->IsFinish())
	{
		Vec2 vTargetPos = m_pTarget->GetPos();

		// Player 가 오른쪽에 있고, 내가 왼쪽에 있을 경우
		if (vTargetPos.x > 2260.f && pOwner->GetDir())
		{
			GetOwnerSM()->ChangeState((UINT)POPE::SPELL);
		}
		// Player가 왼쪽에 있고, 내가 오른쪽에 있는 경우
		else if (vTargetPos.x < 2260.f && !pOwner->GetDir())
		{
			GetOwnerSM()->ChangeState((UINT)POPE::SPELL);
		}
		else
		{
			GetOwnerSM()->ChangeState((UINT)POPE::VANISH);
		}

	}

}

void CPopeIdle::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();
	
	m_pTarget = CLevelMgr::GetInst()->GetPenitent();

	int iSpell = *((int*)GetOwnerSM()->GetDataFromBlackboard(L"Spell"));

	if (iSpell == 0)
	{
		m_fDuration = 1.f;
	}
	else if (iSpell == 1)
	{
		m_fDuration = 5.f;
	}
	else if (iSpell == 2)
	{
		m_fDuration = 10.f;
	}


	if (bDir)
	{
		pAnimator->Play(L"Idle", true);
	}
	else
	{
		pAnimator->Play(L"Idle_L", true);
	}
}

void CPopeIdle::Exit()
{
	m_fAcc = 0.f;
	m_fDuration = 0.f;
}

