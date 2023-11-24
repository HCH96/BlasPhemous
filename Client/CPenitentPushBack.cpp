#include "pch.h"
#include "CPenitentPushBack.h"


CPenitentPushBack::CPenitentPushBack()
{
}

CPenitentPushBack::~CPenitentPushBack()
{
}

void CPenitentPushBack::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;

	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	int iCurFrame = pAnimator->GetCurFrame();



	if (m_iPrevFrame == 7 && iCurFrame == 8)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_PUSHBACK", L"sound\\Object\\Player\\PENITENT_PUSHBACK.wav");
		pSound->Play();
	}


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}


	m_iPrevFrame = iCurFrame;
}

void CPenitentPushBack::Enter()
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();
	CMovement* pMovement = pObj->GetComponent<CMovement>();
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CAnimator* pDustAnimator = pObj->GetComponent<CAnimator>(L"Dust_Animator");
	m_bDir = pObj->GetDir();
	pDustAnimator->SetLock(false);

	pMovement->SetMaxSpeed(800.f);

	m_iPrevFrame = 0;

	if (m_bDir)
	{
		pMovement->SetVelocity(Vec2(-1000.f, 0.f));
		pAnimator->Play(L"PushBack", true);
		pEffector->Play(L"PushBackSpark", false);
		pDustAnimator->Play(L"PushBackDust", false);
	}
	else
	{
		pMovement->SetVelocity(Vec2(1000.f, 0.f));
		pAnimator->Play(L"PushBack_L", true);
		pEffector->Play(L"PushBackSpark_L", false);
		pDustAnimator->Play(L"PushBackDust_L", false);
	}


}

void CPenitentPushBack::Exit()
{
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	pMovement->SetMaxSpeed(350.f);

}


