#include "pch.h"
#include "CFoolKnifeIdle.h"

#include "CPenitent.h"

#include "CLevelMgr.h"



CFoolKnifeIdle::CFoolKnifeIdle()
	: m_pTarget(nullptr)
{
}

CFoolKnifeIdle::~CFoolKnifeIdle()
{
}

void CFoolKnifeIdle::finaltick(float _DT)
{
	// 거리 체크
	CObj* pOwner = GetOwnerObj;

	Vec2 vPos = pOwner->GetPos();
	Vec2 vTargetPos = m_pTarget->GetPos();

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


	if (fLength < 300.f)
	{
		if (bDirToTarget != pOwner->GetDir())
		{
			GetOwnerSM()->ChangeState((UINT)FOOL_KNIFE::TURN);
		}
		else if(!pOwner->GetPlatEnd())
		{
			GetOwnerSM()->ChangeState((UINT)FOOL_KNIFE::WALK);
		}
	}

}

void CFoolKnifeIdle::Enter()
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

void CFoolKnifeIdle::Exit()
{
}

