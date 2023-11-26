#include "pch.h"
#include "CPopeIntro.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CPopeIntro::CPopeIntro()
{
}

CPopeIntro::~CPopeIntro()
{
}

void CPopeIntro::finaltick(float _DT)
{
	m_fAcc += _DT;

	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish() && m_fAcc>2.f)
	{
		CLevelMgr::GetInst()->GetCurLevel()->IntroEnd();
		GetOwnerSM()->ChangeState((UINT)POPE::VANISH);
	}

}

void CPopeIntro::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	Vec2 vTargetPos = pOwner->GetPos();

	m_fAcc = 0;

	pOwner->SetPos(Vec2(2380.f, 1750.f));
	pOwner->SetDir(false);



	if (pOwner->GetDir())
	{
		pAnimator->Play(L"Appear", false);
	}
	else
	{
		pAnimator->Play(L"Appear_L", false);
	}


	//sound 

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_HUSK_VANISH_IN_2.0", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_HUSK_VANISH_IN_2.0.wav");
	pSound->Play();

}

void CPopeIntro::Exit()
{
}

