#include "pch.h"
#include "CCrosscrawlerIdle.h"

#include "CLevelMgr.h"

CCrosscrawlerIdle::CCrosscrawlerIdle()
	: m_pTarget(nullptr)
{
}

CCrosscrawlerIdle::~CCrosscrawlerIdle()
{
}

void CCrosscrawlerIdle::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;

	Vec2 vPos = pOwner->GetPos();
	Vec2 vTargetPos = m_pTarget->GetPos();


	// Penitent ������ �Ÿ�, ����
	float fLength = (vTargetPos - vPos).Length();
	bool bDirToTarget = false;

	// ���� üũ
	if ((vTargetPos.x - vPos.x) > 0)
	{
		bDirToTarget = true;
	}
	else
	{
		bDirToTarget = false;
	}

	// �Ÿ��� 300 ���� �� ��
	if (fLength < 300.f)
	{
		// ������ �ٸ��ٸ�
		if (bDirToTarget != pOwner->GetDir())
		{
			GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::TURN);
		}
		else if (fLength > 80.f)
		{
			GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::WALK);
		}
		else
		{
			GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::ATTACK);
		}

	}


}

void CCrosscrawlerIdle::Enter()
{
	m_pTarget = CLevelMgr::GetInst()->GetPenitent();

	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Idle", true);
	}
	else
	{
		pAnimator->Play(L"Idle_L", true);
	}

}

void CCrosscrawlerIdle::Exit()
{
}

