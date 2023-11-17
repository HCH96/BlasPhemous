#include "pch.h"
#include "CShieldMaidenIdle.h"
#include "CShieldMaiden.h"

#include "CLevelMgr.h"
#include "CPenitent.h"


CShieldMaidenIdle::CShieldMaidenIdle()
	:m_pTarget(nullptr)
{
}

CShieldMaidenIdle::~CShieldMaidenIdle()
{
}

void CShieldMaidenIdle::finaltick(float _DT)
{
	// 거리 체크
	CObj* pOwner = GetOwnerObj;
	CShieldMaiden* pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	Vec2 vPos = pOwner->GetPos();
	Vec2 vTargetPos = m_pTarget->GetPos();
	bool bDir = pOwner->GetDir();
	float fLength = (vTargetPos - vPos).Length();


	// 사거리 안으로 들어왔을 때
	if (fLength < 500.f && !pOwner->GetPlatEnd())
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::WALK);
	}

	// 공격 사거리안으로 들어왔을 때
	if (fLength < 80.f)
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::ATTACK);
	}

	// 반대 방향이라면
	if (pAnimator->IsFinish() && !pMon->GetBlock())
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::IDLE);
	}


}

void CShieldMaidenIdle::Enter()
{
	m_pTarget = CLevelMgr::GetInst()->GetPenitent();

	Vec2 vTarget = m_pTarget->GetPos();

	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>(L"Shield_HitBox");
	CShieldMaiden* m_pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	m_pMon->SetStateBlock(true);


	// 오른쪽에 있을 경우
	if (vTarget.x - pOwner->GetPos().x > 0)
	{
		pOwner->SetDir(true);
	}
	else
	{
		pOwner->SetDir(false);
	}


	bool bDir = pOwner->GetDir();
	pCollider->SetTime(0.f);
	if (bDir)
	{
		pAnimator->Play(L"Idle", true);
	}
	else
	{
		pAnimator->Play(L"Idle_L", true);
	}
}

void CShieldMaidenIdle::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CShieldMaiden* m_pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	m_pMon->SetStateBlock(false);
}

