#include "pch.h"
#include "CElderBrotherIdle.h"

CElderBrotherIdle::CElderBrotherIdle()
{
}

CElderBrotherIdle::~CElderBrotherIdle()
{
}

void CElderBrotherIdle::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)ELDERBROTHER::JUMP);
	}


}

void CElderBrotherIdle::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	bool bDir = pOwner->GetDir();


	pCollider->On();
	
	
	if (bDir)
	{
		pAnimator->Play(L"Idle", false);
	}
	else
	{
		pAnimator->Play(L"Idle_L", false);
	}

}

void CElderBrotherIdle::Exit()
{
}

