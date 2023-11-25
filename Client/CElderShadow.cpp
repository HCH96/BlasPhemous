#include "pch.h"
#include "CElderShadow.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CElderShadowAttack.h"
#include "CElderShadowJump.h"
#include "CElderShadowIdle.h"
#include "CElderShdowNone.h"

CElderShadow::CElderShadow()
{
    // Animator
    m_pAnimator = AddComponent<CAnimator>(L"ElderBrotherShadow");

    // Idle
    CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"elderBrother_idle_shadow", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_idle_shadow.png");
    CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"elderBrother_idle_shadow_L", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_idle_shadow.png");

    m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_idle.txt");
    m_pAnimator->LoadAnimation(pTexReverse, L"Idle_L", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_idle.txt", true);

    m_pAnimator->SetAnimDuration(L"Idle", 0.08f);
    m_pAnimator->SetAnimDuration(L"Idle_L", 0.08f);

    // Attack
    pTex = CAssetMgr::GetInst()->LoadTexture(L"elderBrother_attack_shadow", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_attack_shadow.png");
    pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"elderBrother_attack_shadow_L", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_attack_shadow.png");

    m_pAnimator->LoadAnimation(pTex, L"Attack", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_attack.txt");
    m_pAnimator->LoadAnimation(pTexReverse, L"Attack_L", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_attack.txt", true);

    m_pAnimator->SetAnimDuration(L"Attack", 0.08f);
    m_pAnimator->SetAnimDuration(L"Attack_L", 0.08f);

    // Jump
    pTex = CAssetMgr::GetInst()->LoadTexture(L"elderBrother_jump_shadow", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_jump_shadow.png");
    pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"elderBrother_jump_shadow_L", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_jump_shadow.png");

    m_pAnimator->LoadAnimation(pTex, L"Jump", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_jump.txt");
    m_pAnimator->LoadAnimation(pTexReverse, L"Jump_L", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_jump.txt", true);

    m_pAnimator->SetAnimDuration(L"Jump", 0.08f);
    m_pAnimator->SetAnimDuration(L"Jump_L", 0.08f);


    // AI
    m_pAI = AddComponent<CStateMachine>(L"ElderBrotherShadow");

    m_pAI->AddState((UINT)ELDERBROTHER::IDLE, new CElderShadowIdle);
    m_pAI->AddState((UINT)ELDERBROTHER::JUMP, new CElderShadowJump);
    m_pAI->AddState((UINT)ELDERBROTHER::ATTACK, new CElderShadowAttack);
    m_pAI->AddState((UINT)ELDERBROTHER::INTRO, new CElderShdowNone);


    m_pAI->ChangeState((UINT)ELDERBROTHER::INTRO);

}

CElderShadow::~CElderShadow()
{
}


void CElderShadow::tick(float _DT)
{
    Super::tick(_DT);
}

void CElderShadow::render(HDC _dc)
{
    Super::render(_dc);
}

