#include "pch.h"
#include "CPenitentGuardSlide.h"

CPenitentGuardSlide::CPenitentGuardSlide()
	: m_bDir(false)
{
}

CPenitentGuardSlide::~CPenitentGuardSlide()
{
}

void CPenitentGuardSlide::finaltick(float _DT)
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}
}

void CPenitentGuardSlide::Enter()
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();
	CAnimator* pEffector = pObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CMovement* pMovement = pObj->GetComponent<CMovement>();
	m_bDir = pObj->GetDir();

	pMovement->SetMaxSpeed(800.f);


	if (m_bDir)
	{
		pMovement->SetVelocity(Vec2(-1000.f, 0.f));
		pEffector->Play(L"GuardSlideSpark", false);
		pAnimator->Play(L"GuardSlide", true);
	}
	else
	{
		pMovement->SetVelocity(Vec2(1000.f, 0.f));
		pEffector->Play(L"GuardSlideSpark_L", false);
		pAnimator->Play(L"GuardSlide", true);
	}

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_GUARD", L"sound\\Object\\Player\\PENITENT_GUARD.wav");
	pSound->Play();
}

void CPenitentGuardSlide::Exit()
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	pMovement->SetMaxSpeed(350.f);
}

