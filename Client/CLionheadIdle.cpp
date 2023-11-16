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

	// ����
	if (bDirToTarget == bDir && fLength < 200.f)
	{
		GetOwnerSM()->ChangeState((UINT)LIONHEAD::ATTACK);
	}

	// ��Ÿ��� ��� ���
	if (fLength > 500.f)
	{
		// �������� �Ĵٺ��� ���� ��
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
	// ��Ÿ� �ȿ� ���� ���
	else
	{
		// �� �տ� ���� ���
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

