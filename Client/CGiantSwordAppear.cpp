#include "pch.h"
#include "CGiantSwordAppear.h"

#include "CGiantSword.h"

CGiantSwordAppear::CGiantSwordAppear()
{
}

CGiantSwordAppear::~CGiantSwordAppear()
{
}

void CGiantSwordAppear::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)GIANTSWORD::IDLE);
	}
}

void CGiantSwordAppear::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	CGiantSword* pSword = dynamic_cast<CGiantSword*>(pOwner);

	pSword->SetActive(true);

	pSword->SetHP(10.f);

	pAnimator->Play(L"Appear", false);


}

void CGiantSwordAppear::Exit()
{
}

