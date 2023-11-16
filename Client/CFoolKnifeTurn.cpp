#include "pch.h"
#include "CFoolKnifeTurn.h"

CFoolKnifeTurn::CFoolKnifeTurn()
{
}

CFoolKnifeTurn::~CFoolKnifeTurn()
{
}

void CFoolKnifeTurn::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)FOOL_KNIFE::IDLE);
	}

}

void CFoolKnifeTurn::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Turn", true);
	}
	else
	{
		pAnimator->Play(L"Turn_L", true);
	}


}

void CFoolKnifeTurn::Exit()
{
	CObj* pOwner = GetOwnerObj;
	pOwner->SetDir(!pOwner->GetDir());
}

