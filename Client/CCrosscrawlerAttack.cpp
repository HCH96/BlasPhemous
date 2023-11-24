#include "pch.h"
#include "CCrosscrawlerAttack.h"

CCrosscrawlerAttack::CCrosscrawlerAttack()
{
}

CCrosscrawlerAttack::~CCrosscrawlerAttack()
{
}

void CCrosscrawlerAttack::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	bool bDir = pOwner->GetDir();


	CCollider* pHitBox = pOwner->GetComponent<CCollider>(L"Mon_HitBox");
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	int iCurFrame = pAnimator->GetCurFrame();

	if (m_iPrevFrame == 5 && iCurFrame == 6)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"CROSSCRAWLER_ATTACK_1", L"sound\\Object\\Monster\\Normal\\Crosscrawler\\CROSSCRAWLER_ATTACK_1.wav");
		pSound->Play();
	}

	if (m_iPrevFrame == 10 && iCurFrame == 11)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"CROSSCRAWLER_ATTACK_2", L"sound\\Object\\Monster\\Normal\\Crosscrawler\\CROSSCRAWLER_ATTACK_2.wav");
		pSound->Play();
	}

	if (m_iPrevFrame == 16 && iCurFrame == 17)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"CROSSCRAWLER_ATTACK_HIT", L"sound\\Object\\Monster\\Normal\\Crosscrawler\\CROSSCRAWLER_ATTACK_HIT.wav");
		pSound->Play();
	}

	if (pAnimator->GetCurFrame() == 17)
	{
		pHitBox->On();	
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::IDLE);
	}

	m_iPrevFrame = iCurFrame;
}

void CCrosscrawlerAttack::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pHitBox = pOwner->GetComponent<CCollider>(L"Mon_HitBox");
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Attack", false);
		pHitBox->SetOffsetPos(Vec2(-20.f, -70.f));
	}
	else
	{
		pAnimator->Play(L"Attack_L", false);
		pHitBox->SetOffsetPos(Vec2(20.f, -70.f));
	}
	m_iPrevFrame = 0;
}

void CCrosscrawlerAttack::Exit()
{
}
