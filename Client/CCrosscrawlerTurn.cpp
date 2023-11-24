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

	int iCurFrame = pAnimator->GetCurFrame();

	if (m_iPrevFrame == 19 && iCurFrame == 20)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"CROSSCRAWLER_TURN_END", L"sound\\Object\\Monster\\Normal\\Crosscrawler\\CROSSCRAWLER_TURN_END.wav");
		pSound->Play();
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)CROSSCRAWLER::IDLE);
	}

	m_iPrevFrame = iCurFrame;
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

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"CROSSCRAWLER_TURN", L"sound\\Object\\Monster\\Normal\\Crosscrawler\\CROSSCRAWLER_TURN.wav");
	pSound->Play();

	m_iPrevFrame = 0;

}

void CCrosscrawlerTurn::Exit()
{
	CObj* pOwner = GetOwnerObj;
	pOwner->SetDir(!pOwner->GetDir());
}

