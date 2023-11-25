#include "pch.h"
#include "CPenitentDeath.h"

#include "CPenitent.h"

#include "CCamera.h"

CPenitentDeath::CPenitentDeath()
	: SoundPlay(false)
{
}

CPenitentDeath::~CPenitentDeath()
{
}

void CPenitentDeath::finaltick(float _DT)
{
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);


	// ���� Ȯ��
	if (pPenitent)
	{
		if (pPenitent->GetHP() <= 0.f)
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DEATH);
	}

	// ����
	if ((GetOwnerSM()->GetCurState() == (UINT)PENITENT_STATE::DEATH))
	{
		CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
		CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();

		bool bDir = GetOwnerObj->GetDir();
		if (pMovement->IsGround())
		{
			if (!SoundPlay)
			{
				CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_DEATH_DEFAULT", L"sound\\Object\\Player\\PENITENT_DEATH_DEFAULT.wav");
				pSound->Play();
				SoundPlay = true;
			}

			if (bDir)
			{
				pAnimator->PlayNoReset(L"Death", false);
			}
			else
			{
				pAnimator->PlayNoReset(L"Death_L", false);
			}
		}
		

		if (pAnimator->IsFinish())
		{
			// ���� ���� �� ��Ȱ
			pPenitent->SetHP(100.f);

			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DEATH_END);

			CCamera::GetInst()->PenitentDeath(1.5f);


		}
	}

	

}

void CPenitentDeath::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();

	bool bDir = GetOwnerObj->GetDir();

	pAnimator->FindAnimation(L"Death")->Reset();
	pAnimator->FindAnimation(L"Death_L")->Reset();
	pMovement->SetVelocity(Vec2(0.f, 0.f));

	SoundPlay = false;
}

void CPenitentDeath::Exit()
{
}

