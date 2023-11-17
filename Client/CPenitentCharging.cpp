#include "pch.h"
#include "CPenitentCharging.h"

CPenitentCharging::CPenitentCharging()
{
}

CPenitentCharging::~CPenitentCharging()
{
}

void CPenitentCharging::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");

	int iCurFrame = pAnimator->GetCurFrame();

	if (iCurFrame < 19)
	{
		if (!(KEY_PRESSED(KEY::S)))
		{
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::ATTACK);
		}
	}
	else if (iCurFrame >= 20 && iCurFrame < 30)
	{
		if (iCurFrame == 29 && KEY_PRESSED(KEY::S))
			pAnimator->SetFrame(23);
		if (!(KEY_PRESSED(KEY::S)))
		{
			pAnimator->SetFrame(30);
		}
	}

	if (iCurFrame == 33 || iCurFrame == 39 || iCurFrame == 46)
	{
		pHitBox->On();
	}


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}



}

void CPenitentCharging::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	m_bDir = GetOwnerObj->GetDir();

	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");
	pHitBox->SetScale(Vec2(200.f, 150.f));
	pHitBox->SetTime(0.2f);

	if (m_bDir)
	{
		pHitBox->SetOffsetPos(Vec2(80.f, -80.f));
		pAnimator->Play(L"Charging", true);
	}
	else
	{
		pHitBox->SetOffsetPos(Vec2(-80.f, -80.f));
		pAnimator->Play(L"Charging_L", true);
	}
}

void CPenitentCharging::Exit()
{
}

