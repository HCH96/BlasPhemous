#include "pch.h"
#include "CCrosscrawlerTurn.h"

#include "CLevelMgr.h"

#include "CPenitent.h"

CCrosscrawlerTurn::CCrosscrawlerTurn()
{
}

CCrosscrawlerTurn::~CCrosscrawlerTurn()
{
}

void CCrosscrawlerTurn::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::IDLE);
	}
}

void CCrosscrawlerTurn::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Turn", false);
	}
	else
	{
		pAnimator->Play(L"Turn_L", false);
	}
}

void CCrosscrawlerTurn::Exit()
{
	CObj* pOwner = GetOwnerObj;
	pOwner->SetDir(!pOwner->GetDir());
}

