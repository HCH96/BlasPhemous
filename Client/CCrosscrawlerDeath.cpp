#include "pch.h"
#include "CCrosscrawlerDeath.h"

CCrosscrawlerDeath::CCrosscrawlerDeath()
{
}

CCrosscrawlerDeath::~CCrosscrawlerDeath()
{
}

void CCrosscrawlerDeath::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		pOwner->Destroy();
	}

}

void CCrosscrawlerDeath::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	bool bDir = pOwner->GetDir();
	pCollider->SetTime(0.f);
	if (bDir)
	{
		pAnimator->Play(L"Death", false);
	}
	else
	{
		pAnimator->Play(L"Death_L", false);
	}
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"CROSSCRAWLER_DEATH", L"sound\\Object\\Monster\\Normal\\Crosscrawler\\CROSSCRAWLER_DEATH.wav");
	pSound->Play();

}

void CCrosscrawlerDeath::Exit()
{
}

