#include "pch.h"
#include "CPenitentRising.h"

CPenitentRising::CPenitentRising()
{
}

CPenitentRising::~CPenitentRising()
{
}

void CPenitentRising::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	int iCurFrame = pAnimator->GetCurFrame();



	if (m_iPrevFrame == 6 && iCurFrame == 7)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_START_TALK", L"sound\\Object\\Player\\PENITENT_START_TALK.wav");
		pSound->Play();
	}

	m_iPrevFrame = iCurFrame;

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}


}

void CPenitentRising::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();

	pAnimator->Play(L"Rising", false);

	m_iPrevFrame = 0;

	


}

void CPenitentRising::Exit()
{
}


