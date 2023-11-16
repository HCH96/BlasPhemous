#include "pch.h"
#include "CLionheadWalk.h"



CLionheadWalk::CLionheadWalk()
{
}

CLionheadWalk::~CLionheadWalk()
{
}

void CLionheadWalk::finaltick(float _DT)
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

	// 이동
	if (bDir)
	{
		pMovement->SetVelocity(Vec2(100.f, 0.f));
	}
	else
	{
		pMovement->SetVelocity(Vec2(-100.f, 0.f));
	}

	// 오른쪽을 보고 있는 경우
	if (bDir)
	{
		// 타겟이 앞쪽에 있는 경우
		if (bDir == bDirToTarget)
		{
			// 공격 사거리 안에 있는 경우
			if (fLength < 200.f)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::ATTACK);
			}

			// 발판 끝에 있는 경우
			if (pOwner->GetPlatEnd())
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::IDLE);
			}

			// 사거리를 벗어난 경우
			if (fLength > 500.f)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALKBACK);
			}

			
		}
		// 타겟이 뒤쪽에 있는 경우
		else
		{
			if(InitPos.x < vPos.x)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALKBACK);
			}
			else
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::IDLE);
			}

		}

	}
	// 왼쪽을 보고 있는 경우
	else
	{
		// 타겟이 앞쪽에 있는 경우
		if (bDir == bDirToTarget)
		{
			// 공격 사거리 안에 있는 경우
			if (fLength < 200.f)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::ATTACK);
			}

			// 발판 끝에 있는 경우
			if (pOwner->GetPlatEnd())
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::IDLE);
			}

			// 사거리를 벗어난 경우
			if (fLength > 500.f)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALKBACK);
			}


		}
		// 타겟이 뒤쪽에 있는 경우
		else
		{
			if (InitPos.x > vPos.x)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALKBACK);
			}
			else
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::IDLE);
			}

		}
	}
}

void CLionheadWalk::Enter()
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

void CLionheadWalk::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	pMovement->SetVelocity(Vec2(0.f, 0.f));
}

