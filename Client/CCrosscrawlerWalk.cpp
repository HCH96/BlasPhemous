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
	// �Ÿ� üũ
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

	// �̵�
	if (bDir)
	{
		pMovement->SetVelocity(Vec2(50.f, 0.f));
	}
	else
	{
		pMovement->SetVelocity(Vec2(-50.f, 0.f));
	}

	// ���� ��Ÿ������� ������ ��
	if (fLength < 80.f)
	{
		GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::ATTACK);
	}
	

	// �ݴ� �����̶��
	if (bDirToTarget != pOwner->GetDir())
	{
		GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::TURN);
	}


	// ���� ���� �ִٸ�
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

