#include "pch.h"
#include "CPope.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CPopeAppear.h"
#include "CPopeDeath.h"
#include "CPopeIdle.h"
#include "CPopeSpell.h"
#include "CPopeVanish.h"

CPope::CPope()
	: m_pAnimator(nullptr)
	, m_pEffector(nullptr)
	, m_pSymbol(nullptr)
	, m_pCollider(nullptr)
	, m_pBlock(nullptr)
	, m_pAI(nullptr)
	, m_fHP(10.f)
{
	SetName(L"Pope");

	// Animator
	m_pAnimator = AddComponent<CAnimator>(L"Pope");

	// Idle
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Pope_Idle", L"texture\\Monster\\Boss\\Pope\\pope_idle.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Pope_Idle_L", L"texture\\Monster\\Boss\\Pope\\pope_idle.png");

	m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Boss\\Pope\\pope_idle.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Idle_L", L"animdata\\Monster\\Boss\\Pope\\pope_idle.txt", true);

	m_pAnimator->SetAnimDuration(L"Idle", 0.1f);
	m_pAnimator->SetAnimDuration(L"Idle_L", 0.1f);


	// Death
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Pope_Death", L"texture\\Monster\\Boss\\Pope\\pope_death.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Pope_Death_L", L"texture\\Monster\\Boss\\Pope\\pope_death.png");

	m_pAnimator->LoadAnimation(pTex, L"Death", L"animdata\\Monster\\Boss\\Pope\\pope_death.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Death_L", L"animdata\\Monster\\Boss\\Pope\\pope_death.txt", true);

	m_pAnimator->SetAnimDuration(L"Death", 0.08f);
	m_pAnimator->SetAnimDuration(L"Death_L", 0.08f);

	// Appear
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Pope_Appear", L"texture\\Monster\\Boss\\Pope\\pope_appear.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Pope_Appear_L", L"texture\\Monster\\Boss\\Pope\\pope_appear.png");

	m_pAnimator->LoadAnimation(pTex, L"Appear", L"animdata\\Monster\\Boss\\Pope\\pope_appear.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Appear_L", L"animdata\\Monster\\Boss\\Pope\\pope_appear.txt", true);

	m_pAnimator->SetAnimDuration(L"Appear", 0.05f);
	m_pAnimator->SetAnimDuration(L"Appear_L", 0.05f);

	// Spell
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_spellCast", L"texture\\Monster\\Boss\\Pope\\pope_spellCast.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"pope_spellCast_L", L"texture\\Monster\\Boss\\Pope\\pope_spellCast.png");

	m_pAnimator->LoadAnimation(pTex, L"Spell", L"animdata\\Monster\\Boss\\Pope\\pope_spellCast.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Spell_L", L"animdata\\Monster\\Boss\\Pope\\pope_spellCast.txt", true);

	m_pAnimator->SetAnimDuration(L"Spell", 0.065f);
	m_pAnimator->SetAnimDuration(L"Spell_L", 0.065f);

	// Vanish
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_vanishing", L"texture\\Monster\\Boss\\Pope\\pope_vanishing.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"pope_vanishing_L", L"texture\\Monster\\Boss\\Pope\\pope_vanishing.png");

	m_pAnimator->LoadAnimation(pTex, L"Vanish", L"animdata\\Monster\\Boss\\Pope\\pope_vanishing.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Vanish_L", L"animdata\\Monster\\Boss\\Pope\\pope_vanishing.txt", true);

	m_pAnimator->SetAnimDuration(L"Vanish", 0.07f);
	m_pAnimator->SetAnimDuration(L"Vanish_L", 0.07f);


	// Effector
	m_pEffector = AddComponent<CAnimator>(L"Pope_Effector");

	// Yellow -> firebolt
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_spellCast_FXS_Fire", L"texture\\Monster\\Boss\\Pope\\pope_spellCast_FXS.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"pope_spellCast_FXS_Fire_L", L"texture\\Monster\\Boss\\Pope\\pope_spellCast_FXS.png");

	m_pEffector->LoadAnimation(pTex, L"Firebolt", L"animdata\\Monster\\Boss\\Pope\\pope_spellCast_FXS.txt");
	m_pEffector->LoadAnimation(pTexReverse, L"Firebolt_L", L"animdata\\Monster\\Boss\\Pope\\pope_spellCast_FXS.txt", true);

	m_pEffector->SetAnimDuration(L"Firebolt", 0.065f);
	m_pEffector->SetAnimDuration(L"Firebolt_L", 0.065f);

	// Green -> Toxic
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_spellCast_FXS_Toxic", L"texture\\Monster\\Boss\\Pope\\pope_spellCast_FXS_Green.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"pope_spellCast_FXS_Toxic_L", L"texture\\Monster\\Boss\\Pope\\pope_spellCast_FXS_Green.png");

	m_pEffector->LoadAnimation(pTex, L"Toxic", L"animdata\\Monster\\Boss\\Pope\\pope_spellCast_FXS.txt");
	m_pEffector->LoadAnimation(pTexReverse, L"Toxic_L", L"animdata\\Monster\\Boss\\Pope\\pope_spellCast_FXS.txt", true);

	m_pEffector->SetAnimDuration(L"Toxic", 0.065f);
	m_pEffector->SetAnimDuration(L"Toxic_L", 0.065f);

	// Purple -> MagicMissile
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_spellCast_FXS_MagicMissile", L"texture\\Monster\\Boss\\Pope\\pope_spellCast_FXS_Purple.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"pope_spellCast_FXS_MagicMissile_L", L"texture\\Monster\\Boss\\Pope\\pope_spellCast_FXS_Purple.png");

	m_pEffector->LoadAnimation(pTex, L"MagicMissile", L"animdata\\Monster\\Boss\\Pope\\pope_spellCast_FXS.txt");
	m_pEffector->LoadAnimation(pTexReverse, L"MagicMissile_L", L"animdata\\Monster\\Boss\\Pope\\pope_spellCast_FXS.txt", true);

	m_pEffector->SetAnimDuration(L"MagicMissile", 0.065f);
	m_pEffector->SetAnimDuration(L"MagicMissile_L", 0.065f);


	// Effector
	m_pSymbol = AddComponent<CAnimator>(L"Pope_Symbol");


	// Yellow -> firebolt
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"pope_twistedOne_symbol_L", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.png");

	m_pSymbol->LoadAnimation(pTex, L"Firebolt", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbol->LoadAnimation(pTexReverse, L"Firebolt_L", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt", true);

	m_pSymbol->SetAnimDuration(L"Firebolt", 0.065f);
	m_pSymbol->SetAnimDuration(L"Firebolt_L", 0.065f);

	m_pSymbol->SetAnimOffset(L"Firebolt", Vec2(40.f,-50.f));
	m_pSymbol->SetAnimOffset(L"Firebolt_L", Vec2(-40.f,-50.f));

	// Green -> Toxic
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol_Green", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol_Green.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"pope_twistedOne_symbol_Green_L", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol_Green.png");

	m_pSymbol->LoadAnimation(pTex, L"Toxic", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbol->LoadAnimation(pTexReverse, L"Toxic_L", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt", true);

	m_pSymbol->SetAnimDuration(L"Toxic", 0.065f);
	m_pSymbol->SetAnimDuration(L"Toxic_L", 0.065f);

	m_pSymbol->SetAnimOffset(L"Toxic", Vec2(40.f, -50.f));
	m_pSymbol->SetAnimOffset(L"Toxic_L", Vec2(-40.f, -50.f));

	// Purple -> MagicMissile
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol_Purple", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol_Purple.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"pope_twistedOne_symbol_Purple_L", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol_Purple.png");

	m_pSymbol->LoadAnimation(pTex, L"MagicMissile", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbol->LoadAnimation(pTexReverse, L"MagicMissile_L", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt", true);

	m_pSymbol->SetAnimDuration(L"MagicMissile", 0.065f);
	m_pSymbol->SetAnimDuration(L"MagicMissile_L", 0.065f);

	m_pSymbol->SetAnimOffset(L"MagicMissile", Vec2(40.f, -50.f));
	m_pSymbol->SetAnimOffset(L"MagicMissile_L", Vec2(-40.f, -50.f));
	

	// shieldmaiden_blockEffect
	m_pBlock = AddComponent<CAnimator>(L"BlockEffect");
	pTex = CAssetMgr::GetInst()->LoadTexture(L"shieldmaiden_blockEffect", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldmaiden_blockEffect.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"shieldmaiden_blockEffect_L", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldmaiden_blockEffect.png");

	m_pBlock->LoadAnimation(pTex, L"Block", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldmaiden_blockEffect.txt");
	m_pBlock->LoadAnimation(pTexReverse, L"Block_L", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldmaiden_blockEffect.txt", true);

	m_pBlock->SetAnimDuration(L"Block", 0.1f);
	m_pBlock->SetAnimDuration(L"Block_L", 0.1f);


	// AI
	m_pAI = AddComponent<CStateMachine>(L"Pope");

	m_pAI->AddState((UINT)POPE::IDLE, new CPopeIdle);
	m_pAI->AddState((UINT)POPE::APPEAR, new CPopeAppear);
	m_pAI->AddState((UINT)POPE::SPELL, new CPopeSpell);
	m_pAI->AddState((UINT)POPE::VANISH, new CPopeVanish);
	m_pAI->AddState((UINT)POPE::DEATH, new CPopeDeath);

	m_pAI->AddDataToBlackboard(L"Spell", 0);

	// Collider
	m_pCollider = AddComponent<CCollider>(L"Pope");
	m_pCollider->SetScale(Vec2(40.f, 100.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, -50.f));

	m_pAI->ChangeState((UINT)POPE::IDLE);
}

CPope::~CPope()
{
}

void CPope::tick(float _DT)
{
	Super::tick(_DT);
}

void CPope::render(HDC _dc)
{
	Super::render(_dc);
}

void CPope::OnHit()
{
	if (m_pAI->GetCurState() == (UINT)POPE::SPELL)
	{
		// Block
		if (GetDir())
		{
			m_pBlock->Play(L"Block", false);
		}
		else
		{
			m_pBlock->Play(L"Block_L", false);
		}
		return;
	}

	m_fHP -= 1.f;
}

void CPope::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (_pOtherCol->GetName() == L"Penitent_HitBox")
	{
		OnHit();
	}
}

