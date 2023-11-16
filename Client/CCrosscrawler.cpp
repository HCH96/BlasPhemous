#include "pch.h"
#include "CCrosscrawler.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CCrosscrawlerIdle.h"
#include "CCrosscrawlerAttack.h"
#include "CCrosscrawlerDeath.h"
#include "CCrosscrawlerTurn.h"
#include "CCrosscrawlerWalk.h"

CCrosscrawler::CCrosscrawler()
	: m_pAI(nullptr)
	, m_pAnimator(nullptr)
	, m_pMovement(nullptr)
	, m_pCollider(nullptr)
	, m_fHP(5.f)
	, m_pHitBox(nullptr)
{
	// Animator
	m_pAnimator = AddComponent<CAnimator>(L"Crosscrawler");

	// Idle
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Cross_Idle", L"texture\\Monster\\Normal\\Crosscrawler\\crosscrawler_idle.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Cross_Idle_L", L"texture\\Monster\\Normal\\Crosscrawler\\crosscrawler_idle.png");

	m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Normal\\Crosscrawler\\crosscrawler_idle.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Idle_L", L"animdata\\Monster\\Normal\\Crosscrawler\\crosscrawler_idle.txt", true);

	m_pAnimator->SetAnimDuration(L"Idle", 0.08f);
	m_pAnimator->SetAnimDuration(L"Idle_L", 0.08f);


	// Death
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Cross_Death", L"texture\\Monster\\Normal\\Crosscrawler\\crosscrawler_death.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Cross_Death_L", L"texture\\Monster\\Normal\\Crosscrawler\\crosscrawler_death.png");

	m_pAnimator->LoadAnimation(pTex, L"Death", L"animdata\\Monster\\Normal\\Crosscrawler\\crosscrawler_death.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Death_L", L"animdata\\Monster\\Normal\\Crosscrawler\\crosscrawler_death.txt", true);

	m_pAnimator->SetAnimDuration(L"Death", 0.08f);
	m_pAnimator->SetAnimDuration(L"Death_L", 0.08f);

	// Turn
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Cross_Turn", L"texture\\Monster\\Normal\\Crosscrawler\\crosscrawler_turnaround.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Cross_Turn_L", L"texture\\Monster\\Normal\\Crosscrawler\\crosscrawler_turnaround.png");

	m_pAnimator->LoadAnimation(pTex, L"Turn", L"animdata\\Monster\\Normal\\Crosscrawler\\crosscrawler_turnaround.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Turn_L", L"animdata\\Monster\\Normal\\Crosscrawler\\crosscrawler_turnaround.txt", true);

	m_pAnimator->SetAnimDuration(L"Turn", 0.08f);
	m_pAnimator->SetAnimDuration(L"Turn_L", 0.08f);

	// Walk
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Cross_Walk", L"texture\\Monster\\Normal\\Crosscrawler\\crosscrawler_walking.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Cross_Walk_L", L"texture\\Monster\\Normal\\Crosscrawler\\crosscrawler_walking.png");

	m_pAnimator->LoadAnimation(pTex, L"Walk", L"animdata\\Monster\\Normal\\Crosscrawler\\crosscrawler_walking.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Walk_L", L"animdata\\Monster\\Normal\\Crosscrawler\\crosscrawler_walking.txt", true);

	m_pAnimator->SetAnimDuration(L"Walk", 0.08f);
	m_pAnimator->SetAnimDuration(L"Walk_L", 0.08f);

	// Attack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Cross_Attack", L"texture\\Monster\\Normal\\Crosscrawler\\crosscrawler_attack.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Cross_Attack_L", L"texture\\Monster\\Normal\\Crosscrawler\\crosscrawler_attack.png");

	m_pAnimator->LoadAnimation(pTex, L"Attack", L"animdata\\Monster\\Normal\\Crosscrawler\\crosscrawler_attack.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Attack_L", L"animdata\\Monster\\Normal\\Crosscrawler\\crosscrawler_attack.txt", true);

	m_pAnimator->SetAnimDuration(L"Attack", 0.08f);
	m_pAnimator->SetAnimDuration(L"Attack_L", 0.08f);

	// Movement
	m_pMovement = AddComponent<CMovement>(L"Crosscrawler");
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

	// AI
	m_pAI = AddComponent<CStateMachine>(L"FoolKnife");

	m_pAI->AddState((UINT)CROSSCRAWLER::IDLE, new CCrosscrawlerIdle);
	m_pAI->AddState((UINT)CROSSCRAWLER::TURN, new CCrosscrawlerTurn);
	m_pAI->AddState((UINT)CROSSCRAWLER::DEATH, new CCrosscrawlerDeath);
	m_pAI->AddState((UINT)CROSSCRAWLER::ATTACK, new CCrosscrawlerAttack);
	m_pAI->AddState((UINT)CROSSCRAWLER::WALK, new CCrosscrawlerWalk);

	m_pAI->ChangeState((UINT)FOOL_KNIFE::IDLE);
}

CCrosscrawler::CCrosscrawler(const CCrosscrawler& _Origin)
{
}

CCrosscrawler::~CCrosscrawler()
{
}

void CCrosscrawler::tick(float _DT)
{
	if (GetDir())
	{
		m_pCollider->SetOffsetPos(Vec2(-50.f, -50.f));
	}
	else
	{
		m_pCollider->SetOffsetPos(Vec2(50.f, -50.f));
	}

	Super::tick(_DT);

	if (m_fHP <= 0)
	{
		m_pAI->ChangeState((UINT)FOOL_KNIFE::DEATH);
	}
}

void CCrosscrawler::render(HDC _dc)
{

	Super::render(_dc);
}

void CCrosscrawler::OnHit()
{
	m_fHP -= 1.f;
}

void CCrosscrawler::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (_pOtherCol->GetName() == L"Penitent_HitBox" && _pOwnCol->GetName() == L"Crosscrawler")
	{
		OnHit();
	}
}


