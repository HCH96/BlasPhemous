#include "pch.h"
#include "CCrosscrawlerWalk.h"

#include "CLevelMgr.h"
#include "CPenitent.h"

CCrosscrawlerWalk::CCrosscrawlerWalk()
	:m_pTarget(nullptr)
{
}

CCrosscrawlerWalk::~CCrosscrawlerWalk()
{
}

void CCrosscrawlerWalk::finaltick(float _DT)
{
	// 거리 체크
	CObj* pOwner = GetOwnerObj;
	CMovement* pMovement = pOwner->GetComponent<CMovement>();

	Vec2 vPos = pOwner->GetPos();
	Vec2 vTargetPos = m_pTarget->GetPos();
	bool bDir = pOwner->GetDir();

	float fLength = (vTargetPos - vPos).Length();
	bool bDirToTarget = false;

	if ((vTargetPos.x - vPos.x) > 0)
	{
		bDirToTarget = true;
	}
	else
	{
		bDirToTarget = false;
	}

	// 이동
	if (bDir)
	{
		pMovement->SetVelocity(Vec2(50.f, 0.f));
	}
	else
	{
		pMovement->SetVelocity(Vec2(-50.f, 0.f));
	}

	// 공격 사거리안으로 들어왔을 때
	if (fLength < 80.f)
	{
		GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::ATTACK);
	}
	

	// 반대 방향이라면
	if (bDirToTarget != pOwner->GetDir())
	{
		GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::TURN);
	}


	// 발판 끝에 있다면
	if (pOwner->GetPlatEnd() || fLength > 500.f)
	{
		GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::IDLE);
	}

}

void CCrosscrawlerWalk::Enter()
{
	m_pTarget = CLevelMgr::GetInst()->GetPenitent();

	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Walk", true);
	}
	else
	{
		pAnimator->Play(L"Walk_L", true);
	}

}

void CCrosscrawlerWalk::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	pMovement->SetVelocity(Vec2(0.f, 0.f));
}

