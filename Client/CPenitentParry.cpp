#include "pch.h"
#include "CPenitentParry.h"

CPenitentParry::CPenitentParry()
{
}

CPenitentParry::~CPenitentParry()
{
}

void CPenitentParry::finaltick(float _DT)
{
	CObj* pObj = GetOwnerObj;
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(pObj);
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();

	int iParry = pPenitent->GetParry();
	if (pAnimator->GetCurFrame() == 5 && iParry == 1)
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::GUARDSLIDE);
	}

	if (pAnimator->GetCurFrame() > 5 && iParry == 1)
	{
		pPenitent->OnDamaged();
	}

	if (pAnimator->GetCurFrame() == 5 && iParry == 2)
	{
		if (m_bDir)
		{
			pAnimator->PlayNoReset(L"ParrySuccess",false);
		}
		else
		{
			pAnimator->PlayNoReset(L"ParrySuccess_L", false);
		}

	}


	if (pAnimator->IsFinish())
	{
		// 실드처녀한테 맞았을 때
		if (iParry==2)
		{
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::PARRYCOUNTER);
		}
		// 공격 받지 않았을 때
		else 
		{
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
		}
	}


}

void CPenitentParry::Enter()
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();
	m_bDir = pObj->GetDir();



	// 되감기
	pAnimator->Play(L"ParrySuccess", false);
	pAnimator->Play(L"ParrySuccess_L", false);


	if (m_bDir)
	{
		pAnimator->Play(L"Parry", true);
	}
	else
	{
		pAnimator->Play(L"Parry_L", true);
	}


}

void CPenitentParry::Exit()
{
	CObj* pObj = GetOwnerObj;
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(pObj);

	// Parry Flag 돌려주기
	pPenitent->SetParry(0);
}

