#include "pch.h"
#include "CLionheadWalkback.h"

CLionheadWalkback::CLionheadWalkback()
	:m_pTarget(nullptr)
{
}

CLionheadWalkback::~CLionheadWalkback()
{
}

void CLionheadWalkback::finaltick(float _DT)
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

	// �̵�
	if (bDir)
	{
		pMovement->SetVelocity(Vec2(-100.f, 0.f));
	}
	else
	{
		pMovement->SetVelocity(Vec2(100.f, 0.f));
	}

	// �������� ���� �ִ� ���
	if (bDir)
	{
		// Ÿ���� ���ʿ� �ִ� ���
		if (bDir == bDirToTarget)
		{
			// ���� ��Ÿ� �ȿ� �ִ� ���
			if (fLength < 200.f)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::ATTACK);
			}

			if (InitPos.x >= vPos.x)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::IDLE);
			}

			// ��Ÿ� �ȿ� ���� ���
			if (fLength < 500.f)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALK);
			}

		}
		// Ÿ���� ���ʿ� �ִ� ���
		else
		{
			if (InitPos.x >= vPos.x)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::IDLE);
			}
		}

	}
	// ������ ���� �ִ� ���
	else
	{
		// Ÿ���� ���ʿ� �ִ� ���
		if (bDir == bDirToTarget)
		{
			// ���� ��Ÿ� �ȿ� �ִ� ���
			if (fLength < 200.f)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::ATTACK);
			}

			if (InitPos.x <= vPos.x)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::IDLE);
			}

			// ��Ÿ� �ȿ� ���� ���
			if (fLength < 500.f)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::WALK);
			}

		}
		// Ÿ���� ���ʿ� �ִ� ���
		else
		{
			if (InitPos.x <= vPos.x)
			{
				GetOwnerSM()->ChangeState((UINT)LIONHEAD::IDLE);
			}
		}
	}
}

void CLionheadWalkback::Enter()
{
	m_pTarget = CLevelMgr::GetInst()->GetPenitent();

	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"WalkBack", true);
	}
	else
	{
		pAnimator->Play(L"WalkBack_L", true);
	}

}

void CLionheadWalkback::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	pMovement->SetVelocity(Vec2(0.f, 0.f));
}
