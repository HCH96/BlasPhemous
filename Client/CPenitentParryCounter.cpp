#include "pch.h"
#include "CPenitentParryCounter.h"

CPenitentParryCounter::CPenitentParryCounter()
	:m_bDir(false)
{
}

CPenitentParryCounter::~CPenitentParryCounter()
{
}


void CPenitentParryCounter::finaltick(float _DT)
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();
	CCollider* pHitBox = pObj->GetComponent<CCollider>(L"Penitent_HitBox");

	if (pAnimator->GetCurFrame() == 10)
	{
		pHitBox->On();
	}

	// 애니메이션 종료
	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

}

void CPenitentParryCounter::Enter()
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();
	CCollider* pHitBox = pObj->GetComponent<CCollider>(L"Penitent_HitBox");
	pHitBox->SetScale(Vec2(150.f, 110.f));
	pHitBox->SetTime(0.2f);

	m_bDir = pObj->GetDir();

	if (m_bDir)
	{
		pAnimator->Play(L"ParryCounter", true);
		pHitBox->SetOffsetPos(Vec2(100.f, -70.f));
	}
	else
	{
		pAnimator->Play(L"ParryCounter_L", true);
		pHitBox->SetOffsetPos(Vec2(-100.f, -70.f));
	}

}

void CPenitentParryCounter::Exit()
{
}


