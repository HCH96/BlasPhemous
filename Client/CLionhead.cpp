#include "pch.h"
#include "CLionhead.h"

#include "CAssetMgr.h"
#include "CTexture.h"


CLionhead::CLionhead()
	: m_pAI(nullptr)
	, m_pAnimator(nullptr)
	, m_pMovement(nullptr)
	, m_pCollider(nullptr)
	, m_fHP(8.f)
	, m_pHitBox(nullptr)
{
	// Animator
	m_pAnimator = AddComponent<CAnimator>(L"Crosscrawler");

	// Idle
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Lionhead_Idle", L"texture\\Monster\\Normal\\LionHead\\Lionhead_idle_anim.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Lionhead_Idle_L", L"texture\\Monster\\LionHead\\Crosscrawler\\Lionhead_idle_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_idle_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Idle_L", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_idle_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Idle", 0.1f);
	m_pAnimator->SetAnimDuration(L"Idle_L", 0.1f);

	// Walk
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Lionhead_Walk", L"texture\\Monster\\Normal\\LionHead\\Lionhead_walk_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Lionhead_Walk_L", L"texture\\Monster\\LionHead\\Crosscrawler\\Lionhead_walk_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Walk", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_walk_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Walk_L", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_walk_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Walk", 0.1f);
	m_pAnimator->SetAnimDuration(L"Walk_L", 0.1f);

	// WalkBack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Lionhead_WalkBack", L"texture\\Monster\\Normal\\LionHead\\Lionhead_walk_backward_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Lionhead_WalkBack_L", L"texture\\Monster\\LionHead\\Crosscrawler\\Lionhead_walk_backward_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"WalkBack", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_walk_backward_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"WalkBack_L", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_walk_backward_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"WalkBack", 0.1f);
	m_pAnimator->SetAnimDuration(L"WalkBack_L", 0.1f);

	// Attack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Lionhead_Attack", L"texture\\Monster\\Normal\\LionHead\\Lionhead_attack_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Lionhead_Attack_L", L"texture\\Monster\\LionHead\\Crosscrawler\\Lionhead_attack_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Attack", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_attack_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Attack_L", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_attack_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Attack", 0.1f);
	m_pAnimator->SetAnimDuration(L"Attack_L", 0.1f);

	// Movement
	m_pMovement = AddComponent<CMovement>(L"Lionhead");
	m_pMovement->SetMass(1.f);
	m_pMovement->SetFrictionScale(2000.f);
	m_pMovement->UseGravity(true);
	m_pMovement->SetGround(true);

	// Collider
	m_pCollider = AddComponent<CCollider>(L"Crosscrawler");
	m_pCollider->SetScale(Vec2(50.f, 100.f));
	m_pCollider->SetOffsetPos(Vec2(-50.f, -50.f));

	m_pHitBox = AddComponent<CCollider>(L"Mon_HitBox");
	m_pHitBox->SetScale(Vec2(200.f, 100.f));
	m_pHitBox->SetOffsetPos(Vec2(0.f, 0.f));
	m_pHitBox->SetTime(1.f);
	m_pHitBox->Off();
}

CLionhead::CLionhead(const CLionhead& _Origin)
{
}

CLionhead::~CLionhead()
{
}


void CLionhead::tick(float _DT)
{
	Super::tick(_DT);

	if (m_fHP <= 0)
	{
		m_pAI->ChangeState((UINT)FOOL_KNIFE::DEATH);
	}
}

void CLionhead::render(HDC _dc)
{
	Super::render(_dc);

}

void CLionhead::OnHit()
{
	m_fHP -= 1.f;
}

void CLionhead::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (_pOtherCol->GetName() == L"Penitent_HitBox")
	{
		OnHit();
	}
}

