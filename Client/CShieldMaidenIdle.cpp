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
	// �Ÿ� üũ
	CObj* pOwner = GetOwnerObj;
	CShieldMaiden* pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	Vec2 vPos = pOwner->GetPos();
	Vec2 vTargetPos = m_pTarget->GetPos();
	bool bDir = pOwner->GetDir();
	float fLength = (vTargetPos - vPos).Length();


	// ��Ÿ� ������ ������ ��
	if (fLength < 500.f && !pOwner->GetPlatEnd())
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::WALK);
	}

	// ���� ��Ÿ������� ������ ��
	if (fLength < 80.f)
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::ATTACK);
	}

	// �ݴ� �����̶��
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


	// �����ʿ� ���� ���
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

