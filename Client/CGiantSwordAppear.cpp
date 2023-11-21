#include "pch.h"
#include "CGiantSwordAppear.h"

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


	pAnimator->Play(L"Appear", false);


}

void CGiantSwordAppear::Exit()
{
}

