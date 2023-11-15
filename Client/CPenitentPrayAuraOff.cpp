#include "pch.h"
#include "CPenitentPrayAuraOff.h"

#include "CLevelMgr.h"

CPenitentPrayAuraOff::CPenitentPrayAuraOff()
{
}

CPenitentPrayAuraOff::~CPenitentPrayAuraOff()
{
}

void CPenitentPrayAuraOff::finaltick(float _DT)
{
	if (KEY_TAP(KEY::ESC))
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::PRAYEND);
	}
}

void CPenitentPrayAuraOff::Enter()
{
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);
	pPenitent->SetCheckPoint(CLevelMgr::GetInst()->GetCurLeveli());
	pPenitent->SetHP(100.f);
	pPenitent->SetMP(3);
	pPenitent->SetPotionCount(3);

	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	int iDir = GetOwnerObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"PrayingAuraOff", false);
	}
	else
	{
		pAnimator->Play(L"PrayingAuraOff_L", false);
	}
}

void CPenitentPrayAuraOff::Exit()
{
}



