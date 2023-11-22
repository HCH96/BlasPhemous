#include "pch.h"
#include "CGiantSword.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CGiantSwordAppear.h"
#include "CGiantSwordVanish.h"
#include "CGiantSwordIdle.h"
#include "CGiantSwordSpinAttack.h"


CGiantSword::CGiantSword()
	: m_pAI(nullptr)
	, m_pAnimator(nullptr)
	, m_pEye(nullptr)
	, m_fHP(10.f)
	, m_pCollider(nullptr)
	, m_bActive(true)
{
	SetName(L"GiantSword");

	SetScale(Vec2(2.f, 2.f));

	// Animator
	m_pAnimator = AddComponent<CAnimator>(L"GiantSword");

	// Vanish
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_giantSword_teleportIN", L"texture\\Monster\\Boss\\Pontiff\\pontiff_giantSword_teleportIN.png");
	m_pAnimator->LoadAnimation(pTex, L"Vanish", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_giantSword_teleportIN.txt");
	m_pAnimator->SetAnimDuration(L"Vanish", 0.06f);

	// Appear
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_giantSword_teleportOUT", L"texture\\Monster\\Boss\\Pontiff\\pontiff_giantSword_teleportOUT.png");
	m_pAnimator->LoadAnimation(pTex, L"Appear", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_giantSword_teleportOUT.txt");
	m_pAnimator->SetAnimDuration(L"Appear", 0.06f);

	// Idle
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_giantSword", L"texture\\Monster\\Boss\\Pontiff\\pontiff_giantSword.png");
	m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_giantSword.txt");
	m_pAnimator->SetAnimDuration(L"Idle", 0.06f);

	// Animator
	m_pEye = AddComponent<CAnimator>(L"GiantSwordEye");
	
	pTex = CAssetMgr::GetInst()->LoadTexture(L"pontiff_giantSword_irisSprite", L"texture\\Monster\\Boss\\Pontiff\\pontiff_giantSword_irisSprite.png");
	m_pEye->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Boss\\Pontiff\\pontiff_giantSword_irisSprite.txt");
	m_pEye->SetAnimDuration(L"Idle", 0.06f);

	// AI
	m_pAI = AddComponent<CStateMachine>(L"GiantSword");

	m_pAI->AddState((UINT)GIANTSWORD::IDLE, new CGiantSwordIdle);
	m_pAI->AddState((UINT)GIANTSWORD::APPEAR, new CGiantSwordAppear);
	m_pAI->AddState((UINT)GIANTSWORD::VANISH, new CGiantSwordVanish);
	m_pAI->AddState((UINT)GIANTSWORD::SPINATTACK, new CGiantSwordSpinAttack);


	// Collider
	m_pCollider = AddComponent<CCollider>(L"GiantSword");
	m_pCollider->SetScale(Vec2(40.f, 40.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, 0.f));

	m_pAI->ChangeState((UINT)GIANTSWORD::IDLE);

}

CGiantSword::~CGiantSword()
{
}


void CGiantSword::tick(float _DT)
{
	Super::tick(_DT);
}

void CGiantSword::render(HDC _dc)
{
	Super::render(_dc);
}

void CGiantSword::OnHit()
{
	m_fHP -= 1.f;
}

void CGiantSword::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (_pOtherCol->GetName() == L"Penitent_HitBox" && m_pAI->GetCurState() != (UINT)GIANTSWORD::SPINATTACK)
	{
		OnHit();
	}

}

