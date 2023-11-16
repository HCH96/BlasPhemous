#include "pch.h"
#include "CFoolKnife.h"

#include "CAssetMgr.h"

#include "CFoolKnifeDeath.h"
#include "CFoolKnifeIdle.h"
#include "CFoolKnifeTurn.h"
#include "CFoolKnifeWalk.h"


CFoolKnife::CFoolKnife()
	: m_pAI(nullptr)
	, m_pAnimator(nullptr)
	, m_pMovement(nullptr)
	, m_pCollider(nullptr)
	, m_fHP(2.f)
{

	// Animator
	m_pAnimator = AddComponent<CAnimator>(L"FoolKnife");

	// Idle
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Fool_Idle", L"texture\\Monster\\Normal\\Fool_knife\\fool_idle_knife.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Fool_Idle_L", L"texture\\Monster\\Normal\\Fool_knife\\fool_idle_knife.png");

	m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Normal\\Fool_knife\\fool_idle_knife.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Idle_L", L"animdata\\Monster\\Normal\\Fool_knife\\fool_idle_knife.txt", true);

	m_pAnimator->SetAnimDuration(L"Idle", 0.1f);
	m_pAnimator->SetAnimDuration(L"Idle_L", 0.1f);


	// Death
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Fool_Death", L"texture\\Monster\\Normal\\Fool_knife\\Fool_death_knife.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Fool_Death_L", L"texture\\Monster\\Normal\\Fool_knife\\Fool_death_knife.png");

	m_pAnimator->LoadAnimation(pTex, L"Death", L"animdata\\Monster\\Normal\\Fool_knife\\Fool_death_knife.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Death_L", L"animdata\\Monster\\Normal\\Fool_knife\\Fool_death_knife.txt", true);

	m_pAnimator->SetAnimDuration(L"Death", 0.1f);
	m_pAnimator->SetAnimDuration(L"Death_L", 0.1f);

	// Turn
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Fool_Turn", L"texture\\Monster\\Normal\\Fool_knife\\Fool_turn_knife.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Fool_Turn_L", L"texture\\Monster\\Normal\\Fool_knife\\Fool_turn_knife.png");

	m_pAnimator->LoadAnimation(pTex, L"Turn", L"animdata\\Monster\\Normal\\Fool_knife\\Fool_turn_knife.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Turn_L", L"animdata\\Monster\\Normal\\Fool_knife\\Fool_turn_knife.txt", true);

	m_pAnimator->SetAnimDuration(L"Turn", 0.1f);
	m_pAnimator->SetAnimDuration(L"Turn_L", 0.1f);

	// Walk
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Fool_Walk", L"texture\\Monster\\Normal\\Fool_knife\\Fool_walk_knife.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Fool_Walk_L", L"texture\\Monster\\Normal\\Fool_knife\\Fool_walk_knife.png");

	m_pAnimator->LoadAnimation(pTex, L"Walk", L"animdata\\Monster\\Normal\\Fool_knife\\Fool_walk_knife.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Walk_L", L"animdata\\Monster\\Normal\\Fool_knife\\Fool_walk_knife.txt", true);

	m_pAnimator->SetAnimDuration(L"Walk", 0.1f);
	m_pAnimator->SetAnimDuration(L"Walk_L", 0.1f);


	// Movement
	m_pMovement = AddComponent<CMovement>(L"FoolKnife");
	m_pMovement->SetMass(1.f);
	m_pMovement->SetFrictionScale(2000.f);
	m_pMovement->UseGravity(true);
	m_pMovement->SetGround(true);

	// Collider
	m_pCollider = AddComponent<CCollider>(L"FoolKnife");
	m_pCollider->SetScale(Vec2(50.f, 70.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, -60.f));

	// AI
	m_pAI = AddComponent<CStateMachine>(L"FoolKnife");

	m_pAI->AddState((UINT)FOOL_KNIFE::IDLE, new CFoolKnifeIdle);
	m_pAI->AddState((UINT)FOOL_KNIFE::DEATH, new CFoolKnifeDeath);
	m_pAI->AddState((UINT)FOOL_KNIFE::WALK, new CFoolKnifeWalk);
	m_pAI->AddState((UINT)FOOL_KNIFE::TURN, new CFoolKnifeTurn);

	m_pAI->ChangeState((UINT)FOOL_KNIFE::IDLE);

}

CFoolKnife::CFoolKnife(const CFoolKnife& _Origin)
{
}

CFoolKnife::~CFoolKnife()
{
}


void CFoolKnife::tick(float _DT)
{
	Super::tick(_DT);

	if (m_fHP <= 0)
	{
		m_pAI->ChangeState((UINT)FOOL_KNIFE::DEATH);
	}

}

void CFoolKnife::render(HDC _dc)
{


	Super::render(_dc);
}

void CFoolKnife::OnHit()
{
	m_fHP -= 1.f;
}

void CFoolKnife::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (_pOtherCol->GetName() == L"Penitent_HitBox")
	{
		OnHit();
	}
}

