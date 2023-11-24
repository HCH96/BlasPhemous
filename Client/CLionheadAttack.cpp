#include "pch.h"
#include "CLionheadAttack.h"

CLionheadAttack::CLionheadAttack()
{
}

CLionheadAttack::~CLionheadAttack()
{
}

void CLionheadAttack::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	bool bDir = pOwner->GetDir();


	CCollider* pHitBox = pOwner->GetComponent<CCollider>(L"Mon_HitBox");
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->GetCurFrame() == 9 && m_iPrevFrame == 8)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"LEON_START_ATTACK", L"sound\\Object\\Monster\\Normal\\LionHead\\LEON_START_ATTACK.wav");
		pSound->Play();
	}

	if (pAnimator->GetCurFrame() == 12 && m_iPrevFrame == 11)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"LEON_HIT", L"sound\\Object\\Monster\\Normal\\LionHead\\LEON_HIT.wav");
		pSound->Play();
	}


	

	if (pAnimator->GetCurFrame() == 10)
	{
		pHitBox->On();
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)LIONHEAD::IDLE);
	}

	m_iPrevFrame = pAnimator->GetCurFrame();
}

void CLionheadAttack::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pHitBox = pOwner->GetComponent<CCollider>(L"Mon_HitBox");
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Attack", false);
		pHitBox->SetOffsetPos(Vec2(130.f, -70.f));
	}
	else
	{
		pAnimator->Play(L"Attack_L", false);
		pHitBox->SetOffsetPos(Vec2(-130.f, -70.f));
	}
	m_iPrevFrame = 0;
	

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"LEON_PREATTACK", L"sound\\Object\\Monster\\Normal\\LionHead\\LEON_PREATTACK.wav");
	pSound->Play();

}

void CLionheadAttack::Exit()
{
}
