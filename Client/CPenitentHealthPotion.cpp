#include "pch.h"
#include "CPenitentHealthPotion.h"

CPenitentHealthPotion::CPenitentHealthPotion()
{
}

CPenitentHealthPotion::~CPenitentHealthPotion()
{
}

void CPenitentHealthPotion::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();

	// 상태 변화
	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}
}

void CPenitentHealthPotion::Enter()
{
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);

	if (pPenitent == nullptr)
	{
		LOG(LOG_LEVEL::ERR, L"!!State가 잘못 들어있습니다.");
	}

	pPenitent->SetPotionCount(pPenitent->GetPotionCount() - 1);
	pPenitent->SetHP(pPenitent->GetHP() + 20.f);

	if (pPenitent->GetHP() > 100.f)
	{
		pPenitent->SetHP(100.f);
	}
	
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	int iDir = GetOwnerObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"Healthpotion", true);
	}
	else
	{
		pAnimator->Play(L"Healthpotion_L", true);
	}

}

void CPenitentHealthPotion::Exit()
{
}
