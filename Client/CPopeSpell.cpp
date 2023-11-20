#include "pch.h"
#include "CPopeSpell.h"

#include "CPope.h"
#include "CFireboltSpawner.h"
#include "CMagicMissileSpawner.h"

CPopeSpell::CPopeSpell()
	:m_iSpellIdx(0)
	, m_iPrevFrame(0)
{
}


CPopeSpell::~CPopeSpell()
{
}

void CPopeSpell::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	int iCurFrame = pAnimator->GetCurFrame();


	if (m_iPrevFrame == 27 && iCurFrame == 28)
	{
		CPope* pPope = dynamic_cast<CPope*>(pOwner);
		


		if (m_iSpellIdx == 0)
		{
			CFireboltSpawner* pSpawner = pPope->GetFireSpawner();
			pSpawner->On(pOwner->GetPos());
		}
		else if (m_iSpellIdx == 1)
		{


		}
		else if (m_iSpellIdx == 2)
		{
			CMagicMissileSpawner* pSpawner = pPope->GetMagicSpawner();
			pSpawner->On(pOwner->GetPos(), pOwner->GetDir());
		}
		else
		{
			assert(nullptr);
		}
	}

	

	m_iPrevFrame = iCurFrame;


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


	m_iSpellIdx = 2;

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

