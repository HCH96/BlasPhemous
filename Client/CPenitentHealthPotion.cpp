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
