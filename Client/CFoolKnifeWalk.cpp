#include "pch.h"
#include "CFoolKnifeWalk.h"

#include "CLevelMgr.h"

CFoolKnifeWalk::CFoolKnifeWalk()
	: m_pTarget(nullptr)
{
}

CFoolKnifeWalk::~CFoolKnifeWalk()
{
}

void CFoolKnifeWalk::finaltick(float _DT)
{
	// 거리 체크
	CObj* pOwner = GetOwnerObj;
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	int iCurFrame = pAnimator->GetCurFrame();


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


	if (bDir)
	{
		pMovement->SetVelocity(Vec2(50.f, 0.f));
	}
	else
	{
		pMovement->SetVelocity(Vec2(-50.f, 0.f));
	}

	if (bDirToTarget != pOwner->GetDir())
	{
		GetOwnerSM()->ChangeState((UINT)FOOL_KNIFE::TURN);
	}


	if (pOwner->GetPlatEnd())
	{
		GetOwnerSM()->ChangeState((UINT)FOOL_KNIFE::IDLE);
	}

	if (m_iPrevFrame == 0 && iCurFrame == 1)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"FOOL_FOOTSTEP_1", L"sound\\Object\\Monster\\Normal\\Fool\\FOOL_FOOTSTEP_1.wav");
		pSound->Play();
	}

	if (m_iPrevFrame == 3 && iCurFrame == 4)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"FOOL_FOOTSTEP_2", L"sound\\Object\\Monster\\Normal\\Fool\\FOOL_FOOTSTEP_2.wav");
		pSound->Play();
	}

	if (m_iPrevFrame == 7 && iCurFrame == 8)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"FOOL_FOOTSTEP_3", L"sound\\Object\\Monster\\Normal\\Fool\\FOOL_FOOTSTEP_3.wav");
		pSound->Play();
	}

	m_iPrevFrame = iCurFrame;

}

void CFoolKnifeWalk::Enter()
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


	m_iPrevFrame = 0;
}

void CFoolKnifeWalk::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	pMovement->SetVelocity(Vec2(0.f, 0.f));
}
