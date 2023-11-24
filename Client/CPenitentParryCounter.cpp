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
		if (m_iPrevFrame == 9)
		{
			CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_PARRY_HIT", L"sound\\Object\\Player\\PENITENT_PARRY_HIT.wav");
			pSound->Play();
		}

		pHitBox->On();
	}

	// 애니메이션 종료
	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	m_iPrevFrame = pAnimator->GetCurFrame();

}

void CPenitentParryCounter::Enter()
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();
	CCollider* pHitBox = pObj->GetComponent<CCollider>(L"Penitent_HitBox");
	pHitBox->SetScale(Vec2(150.f, 110.f));
	pHitBox->SetTime(0.2f);

	m_bDir = pObj->GetDir();
	m_iPrevFrame = 0;

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


