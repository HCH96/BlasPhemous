#include "pch.h"
#include "CShieldMaidenWalk.h"

#include "CLevelMgr.h"
#include "CPenitent.h"
#include "CShieldMaiden.h"

CShieldMaidenWalk::CShieldMaidenWalk()
	: m_pTarget(nullptr)
{
}

CShieldMaidenWalk::~CShieldMaidenWalk()
{
}

void CShieldMaidenWalk::finaltick(float _DT)
{
	// 거리 체크
	CObj* pOwner = GetOwnerObj;
	CShieldMaiden* pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	Vec2 vPos = pOwner->GetPos();
	Vec2 vTargetPos = m_pTarget->GetPos();
	bool bDir = pOwner->GetDir();
	float fLength = (vTargetPos - vPos).Length();


	// 이동
	if (bDir)
	{
		pMovement->SetVelocity(Vec2(100.f, 0.f));
	}
	else
	{
		pMovement->SetVelocity(Vec2(-100.f, 0.f));
	}

	// 공격 사거리안으로 들어왔을 때
	if (fLength < 80.f)
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::ATTACK);
	}


	// 반대 방향이라면
	if (!pMon->GetBlock())
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::IDLE);
	}

	// 발판 끝에 있다면
	if (pOwner->GetPlatEnd() || fLength > 500.f)
	{
		GetOwnerSM()->ChangeState((UINT)SHIELDMAIDEN::IDLE);
	}

}

void CShieldMaidenWalk::Enter()
{
	m_pTarget = CLevelMgr::GetInst()->GetPenitent();

	CObj* pOwner = GetOwnerObj;
	CShieldMaiden* m_pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	m_pMon->SetStateBlock(true);

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

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"SHIELD_ENEMY_WALK", L"sound\\Object\\Monster\\Normal\\Shieldmaiden\\SHIELD_ENEMY_WALK.wav");
	pSound->Play(true);
}

void CShieldMaidenWalk::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	pMovement->SetVelocity(Vec2(0.f, 0.f));

	CShieldMaiden* m_pMon = dynamic_cast<CShieldMaiden*>(pOwner);
	m_pMon->SetStateBlock(false);

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"SHIELD_ENEMY_WALK", L"sound\\Object\\Monster\\Normal\\Shieldmaiden\\SHIELD_ENEMY_WALK.wav");
	pSound->Stop();
}

