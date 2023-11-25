#include "pch.h"
#include "CPenitentIntro.h"

CPenitentIntro::CPenitentIntro()
{
}

CPenitentIntro::~CPenitentIntro()
{
}

void CPenitentIntro::finaltick(float _DT)
{
	GetOwnerObj->SetDir(m_bDir);

}

void CPenitentIntro::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(60.f);
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	int iDir = GetOwnerObj->GetDir();
	// Vec2(60.f, -230.f);

	if (iDir)
	{
		pAnimator->Play(L"Idle", true);
	}
	else
	{
		pAnimator->Play(L"Idle_L", true);
	}

	m_bDir = iDir;

}

void CPenitentIntro::Exit()
{
}
