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
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Death", false);
	}
	else
	{
		pAnimator->Play(L"Death_L", false);
	}

}

void CCrosscrawlerDeath::Exit()
{
}

