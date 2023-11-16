#include "pch.h"
#include "CLionheadIdle.h"

CLionheadIdle::CLionheadIdle()
	: m_pTarget(nullptr)
{
}

CLionheadIdle::~CLionheadIdle()
{
}

void CLionheadIdle::finaltick(float _DT)
{
	// Init Position
	Vec2* pInitPos = (Vec2*)GetOwnerSM()->GetDataFromBlackboard(L"Init Position");
	Vec2 InitPos = *pInitPos;


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

	// 공격
	if (bDirToTarget == bDir && fLength < 200.f)
	{
		GetOwnerSM()->ChangeState((UINT)LIONHEAD::ATTACK);
	}

	// 사거리를 벗어난 경우
	if (fLength > 500.f)
	{
		// 오른쪽을 쳐다보고 있을 때
		if (bDir)
		{
			if (InitPos.x < vPos.x)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALKBACK);
			}
		}
		else
		{
			if (InitPos.x > vPos.x)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALKBACK);
			}
		}
	}
	// 사거리 안에 있을 경우
	else
	{
		// 내 앞에 있을 경우
		if (bDirToTarget == bDir)
		{
			if (!pOwner->GetPlatEnd())
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALK);
			}
		}
		else
		{
			if (bDir)
			{
				if (InitPos.x < vPos.x)
				{
					GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALKBACK);
				}
			}
			else
			{
				if (InitPos.x > vPos.x)
				{
					GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALKBACK);
				}
			}
		}
	}


}

void CLionheadIdle::Enter()
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

void CLionheadIdle::Exit()
{
}

