#include "pch.h"
#include "Pontiff.h"

#include "CAssetMgr.h"
#include "CTexture.h"


Pontiff::Pontiff()
	: m_pSword(nullptr)
	, m_pHelmet(nullptr)
	, m_pFace(nullptr)
	, m_pBody(nullptr)
	, m_pSymbolLeft(nullptr)
	, m_pSymbolRight(nullptr)
	, m_pColldier(nullptr)
	, m_pPatternAI(nullptr)
	, m_pAI(nullptr)
	, m_fHP(10.f)
	, m_pToxicSpawner(nullptr)
	, m_pLightningSpawner(nullptr)
{
	SetScale(Vec2(2.f, 2.f));

	// Helmet Animator
	m_pHelmet = AddComponent<CAnimator>(L"Pontiff_Helmet");

	// Closing
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_closing_helmet", L"texture\\Monster\\Boss\\Pontiff\\pontiff_closing_helmet.png");
	m_pHelmet->LoadAnimation(pTex, L"Closing", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_closing_helmet.txt");
	m_pHelmet->SetAnimDuration(L"Closing", 0.1f);

	// Opening
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_opening_helmet", L"texture\\Monster\\Boss\\Pontiff\\pontiff_opening_helmet.png");
	m_pHelmet->LoadAnimation(pTex, L"Opening", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_opening_helmet.txt");
	m_pHelmet->SetAnimDuration(L"Opening", 0.1f);

	// pontiff_idle_helmet
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_idle_helmet", L"texture\\Monster\\Boss\\Pontiff\\pontiff_idle_helmet.png");
	m_pHelmet->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_idle_helmet.txt");
	m_pHelmet->SetAnimDuration(L"Idle", 0.1f);

	// ============================================================================================================================================

	// body Animator
	m_pBody = AddComponent<CAnimator>(L"Pontiff_Body");
	
	// Opening
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_opening_torso", L"texture\\Monster\\Boss\\Pontiff\\pontiff_opening_torso.png");
	m_pBody->LoadAnimation(pTex, L"Opening", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_opening_torso.txt");
	m_pBody->SetAnimDuration(L"Opening", 0.1f);

	// Idle
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_idle_torso", L"texture\\Monster\\Boss\\Pontiff\\pontiff_idle_torso.png");
	m_pBody->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_idle_torso.txt");
	m_pBody->SetAnimDuration(L"Idle", 0.1);

	// Closing
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_closing_torso", L"texture\\Monster\\Boss\\Pontiff\\pontiff_closing_torso.png");
	m_pBody->LoadAnimation(pTex, L"Closing", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_closing_torso.txt");
	m_pBody->SetAnimDuration(L"Closing", 0.1f);




	// =============================================================================================================================================
	// Face Animator
	m_pFace = AddComponent<CAnimator>(L"Pontiff_Helmet");

	// Opening
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_opening_face", L"texture\\Monster\\Boss\\Pontiff\\pontiff_opening_face.png");
	m_pFace->LoadAnimation(pTex, L"Opening", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_opening_face.txt");
	m_pFace->SetAnimDuration(L"Opening", 0.1f);

	// OpenIdle
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_openIdle_face", L"texture\\Monster\\Boss\\Pontiff\\pontiff_openIdle_face.png");
	m_pFace->LoadAnimation(pTex, L"OpenIdle", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_openIdle_face.txt");
	m_pFace->SetAnimDuration(L"OpenIdle", 0.1f);

	// Death
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_openedIdle_face_DEATH", L"texture\\Monster\\Boss\\Pontiff\\pontiff_openedIdle_face_DEATH.png");
	m_pFace->LoadAnimation(pTex, L"Death", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_openedIdle_face_DEATH.txt");
	m_pFace->SetAnimDuration(L"Death", 0.1f);

	// Closing
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_closing_face", L"texture\\Monster\\Boss\\Pontiff\\pontiff_closing_face.png");
	m_pFace->LoadAnimation(pTex, L"Closing", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_closing_face.txt");
	m_pFace->SetAnimDuration(L"Closing", 0.1f);

	// =============================================================================================================================================
	// SymbolLeft

	m_pSymbolLeft = AddComponent<CAnimator>(L"Pope_Symbol");


	// Yellow -> firebolt
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.png");
	m_pSymbolLeft->LoadAnimation(pTex, L"Firebolt", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbolLeft->SetAnimDuration(L"Firebolt", 0.065f);
	m_pSymbolLeft->SetAnimOffset(L"Firebolt", Vec2(-150.f, -280.f));

	// Green -> Toxic
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol_Green", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol_Green.png");
	m_pSymbolLeft->LoadAnimation(pTex, L"Toxic", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbolLeft->SetAnimDuration(L"Toxic", 0.065f);
	m_pSymbolLeft->SetAnimOffset(L"Toxic", Vec2(-150.f, -280.f));

	// Purple -> MagicMissile
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol_Purple", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol_Purple.png");
	m_pSymbolLeft->LoadAnimation(pTex, L"MagicMissile", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbolLeft->SetAnimDuration(L"MagicMissile", 0.065f);
	m_pSymbolLeft->SetAnimOffset(L"MagicMissile", Vec2(-150.f, -280.f));

	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol_Blue", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol_Blue.png");
	m_pSymbolLeft->LoadAnimation(pTex, L"Lightning", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbolLeft->SetAnimDuration(L"Lightning", 0.065f);
	m_pSymbolLeft->SetAnimOffset(L"Lightning", Vec2(-150.f, -280.f));


	// =============================================================================================================================================
	// SymbolRight

	m_pSymbolRight = AddComponent<CAnimator>(L"Pope_Symbol");


	// Yellow -> firebolt
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.png");
	m_pSymbolRight->LoadAnimation(pTex, L"Firebolt", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbolRight->SetAnimDuration(L"Firebolt", 0.065f);
	m_pSymbolRight->SetAnimOffset(L"Firebolt", Vec2(150.f, -280.f));

	// Green -> Toxic
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol_Green", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol_Green.png");
	m_pSymbolRight->LoadAnimation(pTex, L"Toxic", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbolRight->SetAnimDuration(L"Toxic", 0.065f);
	m_pSymbolRight->SetAnimOffset(L"Toxic", Vec2(150.f, -280.f));

	// Purple -> MagicMissile
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol_Purple", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol_Purple.png");
	m_pSymbolRight->LoadAnimation(pTex, L"MagicMissile", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbolRight->SetAnimDuration(L"MagicMissile", 0.065f);
	m_pSymbolRight->SetAnimOffset(L"MagicMissile", Vec2(150.f, -280.f));

	pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_twistedOne_symbol_Blue", L"texture\\Monster\\Boss\\Pope\\pope_twistedOne_symbol_Blue.png");
	m_pSymbolRight->LoadAnimation(pTex, L"Lightning", L"animdata\\Monster\\Boss\\Pope\\pope_twistedOne_symbol.txt");
	m_pSymbolRight->SetAnimDuration(L"Lightning", 0.065f);
	m_pSymbolRight->SetAnimOffset(L"Lightning", Vec2(150.f, -280.f));





	m_pHelmet->Play(L"Closing", true);
	m_pBody->Play(L"Closing", true);
	//m_pFace->Stop();

	m_pSymbolLeft->Play(L"Firebolt", false);
	m_pSymbolRight->Play(L"Firebolt", false);




}

Pontiff::~Pontiff()
{
}


void Pontiff::tick(float _DT)
{
	Super::tick(_DT);
}

void Pontiff::render(HDC _dc)
{


	Super::render(_dc);
}

void Pontiff::OnHit()
{
}

void Pontiff::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
}
