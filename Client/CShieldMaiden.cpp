#include "pch.h"
#include "CShieldMaiden.h"


#include "CAssetMgr.h"
#include "CTexture.h"
#include "CLevelMgr.h"


#include "CLevelMgr.h"
#include "CPenitent.h"

#include "CShieldMaidenWalk.h"
#include "CShieldMaidenAttack.h"
#include "CShieldMaidenDeath.h"
#include "CShieldMaidenIdle.h"
#include "CShieldMaidenParryReaction.h"
#include "CShieldMaidenStun.h"
#include "CShieldMaidenToIdle.h"

CShieldMaiden::CShieldMaiden()
	: m_pAI(nullptr)
	, m_pAnimator(nullptr)
	, m_pEffector(nullptr)
	, m_pMovement(nullptr)
	, m_pCollider(nullptr)
	, m_fHP(5.f)
	, m_pHitBox(nullptr)
	, m_bIsBlock(true)
	, m_bStateBlock(true)
{
	SetDir(false);

	// Animator
	m_pAnimator = AddComponent<CAnimator>(L"ShieldMaiden");

	// Idle
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Shieldandsword_idle", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldandsword_idle.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Lionhead_Idle_L", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldandsword_idle.png");

	m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldandsword_idle.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Idle_L", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldandsword_idle.txt", true);

	m_pAnimator->SetAnimDuration(L"Idle", 0.1f);
	m_pAnimator->SetAnimDuration(L"Idle_L", 0.1f);

	// Death
	pTex = CAssetMgr::GetInst()->LoadTexture(L"shieldandsword_death", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldandsword_death.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"shieldandsword_death_L", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldandsword_death.png");

	m_pAnimator->LoadAnimation(pTex, L"Death", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldandsword_death.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Death_L", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldandsword_death.txt", true);

	m_pAnimator->SetAnimDuration(L"Death", 0.1f);
	m_pAnimator->SetAnimDuration(L"Death_L", 0.1f);

	// attack shieldMaiden_attack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"shieldMaiden_attack", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_attack.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"shieldMaiden_attack_L", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_attack.png");

	m_pAnimator->LoadAnimation(pTex, L"Attack", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_attack.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Attack_L", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_attack.txt", true);

	m_pAnimator->SetAnimDuration(L"Attack", 0.1f);
	m_pAnimator->SetAnimDuration(L"Attack_L", 0.1f);

	// shieldMaiden_parryReaction
	pTex = CAssetMgr::GetInst()->LoadTexture(L"shieldMaiden_parryReaction", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_parryReaction.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"shieldMaiden_parryReaction_L", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_parryReaction.png");

	m_pAnimator->LoadAnimation(pTex, L"ParryReaction", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_parryReaction.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"ParryReaction_L", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_parryReaction.txt", true);

	m_pAnimator->SetAnimDuration(L"ParryReaction", 0.1f);
	m_pAnimator->SetAnimDuration(L"ParryReaction_L", 0.1f);

	// ToIdle

	pTex = CAssetMgr::GetInst()->LoadTexture(L"shieldMaiden_parryReactionToIdle", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_parryReactionToIdle.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"shieldMaiden_parryReactionToIdle_L", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_parryReactionToIdle.png");

	m_pAnimator->LoadAnimation(pTex, L"ToIdle", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_parryReactionToIdle.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"ToIdle_L", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_parryReactionToIdle.txt", true);

	m_pAnimator->SetAnimDuration(L"ToIdle", 0.1f);
	m_pAnimator->SetAnimDuration(L"ToIdle_L", 0.1f);

	// Walk

	pTex = CAssetMgr::GetInst()->LoadTexture(L"shieldMaiden_walking_anim", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_walking_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"shieldMaiden_walking_anim_L", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_walking_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Walk", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_walking_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Walk_L", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_walking_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Walk", 0.1f);
	m_pAnimator->SetAnimDuration(L"Walk_L", 0.1f);

	// shieldMaiden_stun
	pTex = CAssetMgr::GetInst()->LoadTexture(L"shieldMaiden_stun", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_stun.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"shieldMaiden_stun_L", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_stun.png");

	m_pAnimator->LoadAnimation(pTex, L"Stun", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_stun.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Stun_L", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldMaiden_stun.txt", true);

	m_pAnimator->SetAnimDuration(L"Stun", 0.1f);
	m_pAnimator->SetAnimDuration(L"Stun_L", 0.1f);

	// shieldmaiden_blockEffect
	m_pEffector = AddComponent<CAnimator>(L"Effector");
	pTex = CAssetMgr::GetInst()->LoadTexture(L"shieldmaiden_blockEffect", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldmaiden_blockEffect.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"shieldmaiden_blockEffect_L", L"texture\\Monster\\Normal\\ShieldMaiden\\shieldmaiden_blockEffect.png");

	m_pEffector->LoadAnimation(pTex, L"Block", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldmaiden_blockEffect.txt");
	m_pEffector->LoadAnimation(pTexReverse, L"Block_L", L"animdata\\Monster\\Normal\\ShieldMaiden\\shieldmaiden_blockEffect.txt", true);

	m_pEffector->SetAnimDuration(L"Block", 0.1f);
	m_pEffector->SetAnimDuration(L"Block_L", 0.1f);


	// Movement
	m_pMovement = AddComponent<CMovement>(L"ShieldMaiden");
	m_pMovement->SetMass(1.f);
	m_pMovement->SetFrictionScale(2000.f);
	m_pMovement->UseGravity(true);
	m_pMovement->SetGround(true);

	// AI
	m_pAI = AddComponent<CStateMachine>(L"ShieldMaiden");

	m_pAI->AddState((UINT)SHIELDMAIDEN::IDLE, new CShieldMaidenIdle);
	m_pAI->AddState((UINT)SHIELDMAIDEN::ATTACK, new CShieldMaidenAttack);
	m_pAI->AddState((UINT)SHIELDMAIDEN::DEATH, new CShieldMaidenDeath);
	m_pAI->AddState((UINT)SHIELDMAIDEN::PARRYREACTION, new CShieldMaidenParryReaction);
	m_pAI->AddState((UINT)SHIELDMAIDEN::STUN, new CShieldMaidenStun);
	m_pAI->AddState((UINT)SHIELDMAIDEN::TOIDLE, new CShieldMaidenToIdle);
	m_pAI->AddState((UINT)SHIELDMAIDEN::WALK, new CShieldMaidenWalk);

	

	// Collider
	m_pCollider = AddComponent<CCollider>(L"ShieldMaiden");
	m_pCollider->SetScale(Vec2(80.f, 100.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, -50.f));

	m_pHitBox = AddComponent<CCollider>(L"Shield_HitBox");
	m_pHitBox->SetScale(Vec2(100.f, 100.f));
	m_pHitBox->SetOffsetPos(Vec2(0.f, 0.f));
	m_pHitBox->SetTime(0.5f);
	m_pHitBox->Off();

	m_pAI->ChangeState((UINT)SHIELDMAIDEN::IDLE);
}

CShieldMaiden::CShieldMaiden(const CShieldMaiden& _Origin)
{
}

CShieldMaiden::~CShieldMaiden()
{
}

void CShieldMaiden::begin()
{
}

void CShieldMaiden::tick(float _DT)
{
	Super::tick(_DT);

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	Vec2 vTarget = pPenitent->GetPos();
	Vec2 vPos = GetPos();
	bool bDir = GetDir();

	// 타겟이 나보다 오른쪽에 있을 때
	if ((vTarget.x - vPos.x) > 0 )
	{
		if(bDir)
			m_bIsBlock = true;
		else
			m_bIsBlock = false;

	}	
	else if ((vTarget.x - vPos.x) < 0)
	{
		if (!bDir)
		{
			m_bIsBlock = true;
		}
		else
		{
			m_bIsBlock = false;
		}
	}
		






	if (m_fHP <= 0)
	{
		m_pAI->ChangeState((UINT)SHIELDMAIDEN::DEATH);
	}
}

void CShieldMaiden::render(HDC _dc)
{
	Super::render(_dc);
}

void CShieldMaiden::OnHit()
{
	// 뒤에서 때린 경우
	if (!m_bIsBlock)
	{
		//Hit
		m_fHP -= 1.f;
	}
	// 앞에서 때린 경우
	else
	{
		CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
		CStateMachine* pSM = pPenitent->GetComponent<CStateMachine>();
		


		if (pSM->GetCurState() == (UINT)PENITENT_STATE::PARRYCOUNTER)
		{
			m_pAI->ChangeState((UINT)SHIELDMAIDEN::STUN);
		}

		// 막기가 가능한 State
		if (m_bStateBlock)
		{
			// 막힘
			if (GetDir())
			{
				m_pEffector->Play(L"Block", false);
			}
			else
			{
				m_pEffector->Play(L"Block_L", false);
			}
		}
		else
		{
			// Hit
			m_fHP -= 1.f;
			return;
		}

	}
}

void CShieldMaiden::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (_pOtherCol->GetName() == L"Penitent_HitBox" && _pOwnCol->GetName() == L"ShieldMaiden")
	{
		OnHit();
	}
}



