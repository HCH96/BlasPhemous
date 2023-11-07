#include "pch.h"
#include "CPenitentDeath.h"

#include "CPenitent.h"

CPenitentDeath::CPenitentDeath()
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
			GetOwnerSM()->RevertToPrevState();
		}
	}

	

}

void CPenitentDeath::Enter()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();

	bool bDir = GetOwnerObj->GetDir();

	
	pMovement->SetVelocity(Vec2(0.f, 0.f));
}

void CPenitentDeath::Exit()
{
}

