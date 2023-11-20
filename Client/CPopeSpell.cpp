#include "pch.h"
#include "CPopeSpell.h"

CPopeSpell::CPopeSpell()
	:m_iSpellIdx(0)
{
}


CPopeSpell::~CPopeSpell()
{
}

void CPopeSpell::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)POPE::IDLE);
	}

}

void CPopeSpell::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CAnimator* pEffector = pOwner->GetComponent<CAnimator>(L"Pope_Effector");
	CAnimator* pSymbol = pOwner->GetComponent<CAnimator>(L"Pope_Symbol");


	// 0 firebolt / 1 Toxic / 2 magicmissile

	m_iSpellIdx = (rand() % 3);
	GetOwnerSM()->EditDataToBlackboard(L"Spell", m_iSpellIdx);


	bool bDir = pOwner->GetDir();

	if (m_iSpellIdx == 0)
	{
		if (bDir)
		{
			pAnimator->Play(L"Spell", false);
			pEffector->Play(L"Firebolt", false);
			pSymbol->Play(L"Firebolt", false);
		}
		else
		{
			pAnimator->Play(L"Spell_L", false);
			pEffector->Play(L"Firebolt_L", false);
			pSymbol->Play(L"Firebolt_L", false);
		}
	}
	else if(m_iSpellIdx == 1)
	{
		if (bDir)
		{
			pAnimator->Play(L"Spell", false);
			pEffector->Play(L"Toxic", false);
			pSymbol->Play(L"Toxic", false);
		}
		else
		{
			pAnimator->Play(L"Spell_L", false);
			pEffector->Play(L"Toxic_L", false);
			pSymbol->Play(L"Toxic_L", false);
		}

	}
	else if (m_iSpellIdx == 2)
	{
		if (bDir)
		{
			pAnimator->Play(L"Spell", false);
			pEffector->Play(L"MagicMissile", false);
			pSymbol->Play(L"MagicMissile", false);
		}
		else
		{
			pAnimator->Play(L"Spell_L", false);
			pEffector->Play(L"MagicMissile_L", false);
			pSymbol->Play(L"MagicMissile_L", false);
		}
	}
	else
	{
		assert(nullptr);
	}

}

void CPopeSpell::Exit()
{
}

