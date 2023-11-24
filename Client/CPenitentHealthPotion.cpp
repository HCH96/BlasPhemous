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
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");


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
		pEffector->Play(L"HealthPotion", false);
	}
	else
	{
		pAnimator->Play(L"Healthpotion_L", true);
		pEffector->Play(L"HealthPotion_L", false);
	}


	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"USE_FLASK", L"sound\\Effect\\USE_FLASK.wav");
	pSound->SetVolume(80.f);
	pSound->Play();
}

void CPenitentHealthPotion::Exit()
{
}
