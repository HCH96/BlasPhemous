#include "pch.h"
#include "CElderBrotherAttack.h"

#include "CLevelMgr.h"
#include "CObj.h"


CElderBrotherAttack::CElderBrotherAttack()
	: m_pTarget(nullptr)
{
}

CElderBrotherAttack::~CElderBrotherAttack()
{
}


void CElderBrotherAttack::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)ELDERBROTHER::IDLE);
	}

}

void CElderBrotherAttack::Enter()
{
	m_pTarget = CLevelMgr::GetInst()->GetPenitent();
	CObj* pOwner = GetOwnerObj;
	
	Vec2 vTargetPos = m_pTarget->GetPos();
	Vec2 vPos = pOwner->GetPos();

	// 방향 정하기
	if ((vTargetPos.x - vPos.x) > 0)
	{
		pOwner->SetDir(true);
	}
	else
	{
		pOwner->SetDir(false);
	}

	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();
	//pCollider->SetTime(0.f);

	if (bDir)
	{
		pAnimator->Play(L"Attack", false);
	}
	else
	{
		pAnimator->Play(L"Attack_L", false);
	}

}

void CElderBrotherAttack::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	//pCollider->SetTime(-1.f);
	pCollider->On();
}

