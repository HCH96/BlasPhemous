#include "pch.h"
#include "CFoolKnifeDeath.h"

CFoolKnifeDeath::CFoolKnifeDeath()
{
}

CFoolKnifeDeath::~CFoolKnifeDeath()
{
}


void CFoolKnifeDeath::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	int iCurFrame = pAnimator->GetCurFrame();

	if (m_iPrevFrame == 1 && iCurFrame ==2)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"FOOL_DEATH_1", L"sound\\Object\\Monster\\Normal\\Fool\\FOOL_DEATH_1.wav");
		pSound->Play();
	}

	if (pAnimator->IsFinish())
	{
		pOwner->Destroy();
	}

	m_iPrevFrame = iCurFrame;
}

void CFoolKnifeDeath::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	bool bDir = pOwner->GetDir();

	pCollider->SetTime(0.f);

	if (bDir)
	{
		pAnimator->Play(L"Death", true);
	}
	else
	{
		pAnimator->Play(L"Death_L", true);
	}

	m_iPrevFrame = 0;
}

void CFoolKnifeDeath::Exit()
{
	
}

