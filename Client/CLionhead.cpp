#include "pch.h"
#include "CLionhead.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CLionheadAttack.h"
#include "CLionheadDeath.h"
#include "CLionheadIdle.h"
#include "CLionheadWalk.h"
#include "CLionheadWalkback.h"


CLionhead::CLionhead()
	: m_pAI(nullptr)
	, m_pAnimator(nullptr)
	, m_pMovement(nullptr)
	, m_pCollider(nullptr)
	, m_fHP(8.f)
	, m_pHitBox(nullptr)
{
	SetDir(false);

	// Animator
	m_pAnimator = AddComponent<CAnimator>(L"Crosscrawler");

	// Idle
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Lionhead_Idle", L"texture\\Monster\\Normal\\LionHead\\Lionhead_idle_anim.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Lionhead_Idle_L", L"texture\\Monster\\Normal\\LionHead\\Lionhead_idle_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_idle_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Idle_L", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_idle_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Idle", 0.07f);
	m_pAnimator->SetAnimDuration(L"Idle_L", 0.07f);

	// Walk
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Lionhead_Walk", L"texture\\Monster\\Normal\\LionHead\\Lionhead_walk_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Lionhead_Walk_L", L"texture\\Monster\\Normal\\LionHead\\Lionhead_walk_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Walk", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_walk_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Walk_L", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_walk_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Walk", 0.07f);
	m_pAnimator->SetAnimDuration(L"Walk_L", 0.07f);

	// WalkBack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Lionhead_WalkBack", L"texture\\Monster\\Normal\\LionHead\\Lionhead_walk_backward_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Lionhead_WalkBack_L", L"texture\\Monster\\Normal\\LionHead\\Lionhead_walk_backward_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"WalkBack", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_walk_backward_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"WalkBack_L", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_walk_backward_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"WalkBack", 0.07f);
	m_pAnimator->SetAnimDuration(L"WalkBack_L", 0.07f);

	// Attack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Lionhead_Attack", L"texture\\Monster\\Normal\\LionHead\\Lionhead_attack_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Lionhead_Attack_L", L"texture\\Monster\\Normal\\LionHead\\Lionhead_attack_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Attack", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_attack_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Attack_L", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_attack_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Attack", 0.07f);
	m_pAnimator->SetAnimDuration(L"Attack_L", 0.07f);

	// Attack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Lionhead_Death", L"texture\\Monster\\Normal\\LionHead\\Lionhead_death_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Lionhead_Death_L", L"texture\\Monster\\Normal\\LionHead\\Lionhead_death_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Death", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_death_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Death_L", L"animdata\\Monster\\Normal\\LionHead\\Lionhead_death_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Death", 0.07f);
	m_pAnimator->SetAnimDuration(L"Death_L", 0.07f);

	// Movement
	m_pMovement = AddComponent<CMovement>(L"Lionhead");
	m_pMovement->SetMass(1.f);
	m_pMovement->SetFrictionScale(2000.f);
	m_pMovement->UseGravity(true);
	m_pMovement->SetGround(true);

	

	// AI
	m_pAI = AddComponent<CStateMachine>(L"FoolKnife");

	m_pAI->AddState((UINT)LIONHEAD::IDLE, new CLionheadIdle);
	m_pAI->AddState((UINT)LIONHEAD::WALK, new CLionheadWalk);
	m_pAI->AddState((UINT)LIONHEAD::WALKBACK, new CLionheadWalkback);
	m_pAI->AddState((UINT)LIONHEAD::DEATH, new CLionheadDeath);
	m_pAI->AddState((UINT)LIONHEAD::ATTACK, new CLionheadAttack);

	m_pAI->ChangeState((UINT)FOOL_KNIFE::IDLE);

	// Collider
	m_pCollider = AddComponent<CCollider>(L"Lionhead");
	m_pCollider->SetScale(Vec2(80.f, 200.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, -100.f));

	m_pHitBox = AddComponent<CCollider>(L"Mon_HitBox");
	m_pHitBox->SetScale(Vec2(300.f, 200.f));
	m_pHitBox->SetOffsetPos(Vec2(0.f, 0.f));
	m_pHitBox->SetTime(0.5f);
	m_pHitBox->Off();
}

CLionhead::CLionhead(const CLionhead& _Origin)
{
}

CLionhead::~CLionhead()
{
}


void CLionhead::begin()
{
	Vec2 vPos = GetPos();
	m_pAI->AddDataToBlackboard(L"Init Position", vPos);
}

void CLionhead::tick(float _DT)
{
	Super::tick(_DT);

	if (m_fHP <= 0)
	{
		m_pAI->ChangeState((UINT)LIONHEAD::DEATH);
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

	if (_pOtherCol->GetName() == L"Penitent_HitBox" && _pOwnCol->GetName() == L"Lionhead")
	{
		OnHit();
	}
}

void CLionhead::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (_OtherObj->GetLayerIdx() != (UINT)LAYER::PLAYER || _OwnCol->GetName() != L"Lionhead")
		return;

	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vObjPos = _OtherObj->GetPos();
	CMovement* pOtherMovement = _OtherObj->GetComponent<CMovement>();

	if (m_pCollider->GetAngle() == 0.f)
	{
		// 왼쪽으로 충돌했을 경우
		if (vPos.x > vObjPos.x && (pOtherMovement->GetVelocity().x > 0))
		{
			_OtherObj->SetPos(Vec2(vPos.x - _OwnCol->GetScale().x / 2.f - _OtherCol->GetScale().x / 2.f, vObjPos.y));
		}

		// 오른쪽으로 충돌했을 경우
		if (vPos.x < vObjPos.x && (pOtherMovement->GetVelocity().x < 0))
		{
			_OtherObj->SetPos(Vec2(vPos.x + _OwnCol->GetScale().x / 2.f + _OtherCol->GetScale().x / 2.f, vObjPos.y));
		}
	}
}

