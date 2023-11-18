#include "pch.h"
#include "CElderBrother.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CElderBrotherAttack.h"
#include "CElderBrotherDeath.h"
#include "CElderBrotherIdle.h"
#include "CElderBrotherJump.h"


CElderBrother::CElderBrother()
    : m_pAnimator(nullptr)
    , m_pCollider(nullptr)
    , m_pMovement(nullptr)
    , m_pAI(nullptr)
    , m_fHP(12.f)
{
    // Animator
    m_pAnimator = AddComponent<CAnimator>(L"ElderBrother");

    // Idle
    CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Elder_Idle", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_idle.png");
    CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Elder_Idle_L", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_idle.png");

    m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_idle.txt");
    m_pAnimator->LoadAnimation(pTexReverse, L"Idle_L", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_idle.txt", true);

    m_pAnimator->SetAnimDuration(L"Idle", 0.08f);
    m_pAnimator->SetAnimDuration(L"Idle_L", 0.08f);

    // Attack
    pTex = CAssetMgr::GetInst()->LoadTexture(L"Elder_Attack", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_attack.png");
    pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Elder_Attack_L", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_attack.png");

    m_pAnimator->LoadAnimation(pTex, L"Attack", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_attack.txt");
    m_pAnimator->LoadAnimation(pTexReverse, L"Attack_L", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_attack.txt", true);

    m_pAnimator->SetAnimDuration(L"Attack", 0.08f);
    m_pAnimator->SetAnimDuration(L"Attack_L", 0.08f);

    // Jump
    pTex = CAssetMgr::GetInst()->LoadTexture(L"Elder_Jump", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_jump.png");
    pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Elder_Jump_L", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_jump.png");

    m_pAnimator->LoadAnimation(pTex, L"Jump", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_jump.txt");
    m_pAnimator->LoadAnimation(pTexReverse, L"Jump_L", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_jump.txt", true);

    m_pAnimator->SetAnimDuration(L"Jump", 0.08f);
    m_pAnimator->SetAnimDuration(L"Jump_L", 0.08f);

    // Death
    pTex = CAssetMgr::GetInst()->LoadTexture(L"Elder_Death", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_death.png");
    pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Elder_Death_L", L"texture\\Monster\\Boss\\ElderBrother\\elderBrother_death.png");

    m_pAnimator->LoadAnimation(pTex, L"Death", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_death.txt");
    m_pAnimator->LoadAnimation(pTexReverse, L"Death_L", L"animdata\\Monster\\Boss\\ElderBrother\\elderBrother_death.txt", true);

    m_pAnimator->SetAnimDuration(L"Death", 0.08f);
    m_pAnimator->SetAnimDuration(L"Death_L", 0.08f);

    // Movement
    m_pMovement = AddComponent<CMovement>(L"ElderBrother");
    m_pMovement->SetMass(1.f);
    m_pMovement->UseGravity(true);
    m_pMovement->SetGravity(Vec2(0.f, 3000.f));
    m_pMovement->SetJumpVel(-1500.f);
    m_pMovement->SetMaxDown(1000.f);

    // AI
    m_pAI = AddComponent<CStateMachine>(L"ElderBrother");

    m_pAI->AddState((UINT)ELDERBROTHER::IDLE, new CElderBrotherIdle);
    m_pAI->AddState((UINT)ELDERBROTHER::JUMP, new CElderBrotherJump);
    m_pAI->AddState((UINT)ELDERBROTHER::DEATH, new CElderBrotherDeath);
    m_pAI->AddState((UINT)ELDERBROTHER::ATTACK, new CElderBrotherAttack);

    // Collider
    m_pCollider = AddComponent<CCollider>(L"ElderBrother");
    m_pCollider->SetScale(Vec2(40.f, 200.f));
    m_pCollider->SetOffsetPos(Vec2(0.f, -100.f));


    m_pAI->ChangeState((UINT)FOOL_KNIFE::IDLE);

}

CElderBrother::~CElderBrother()
{
}

void CElderBrother::tick(float _DT)
{
    Super::tick(_DT);

    if (m_fHP <= 0)
    {
        m_pAI->ChangeState((UINT)FOOL_KNIFE::DEATH);
    }

    if(KEY_TAP(KEY::Y))
    {
        SetPos(Vec2(1470.f, 1060.f));
    }

}

void CElderBrother::render(HDC _dc)
{
    Super::render(_dc);
}

void CElderBrother::OnHit()
{
    m_fHP -= 1.f;
}

void CElderBrother::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
    if (_pOtherCol->GetName() == L"Penitent_HitBox")
    {
        OnHit();
    }
}

void CElderBrother::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
    if (_OtherObj->GetLayerIdx() != (UINT)LAYER::PLAYER || m_pAI->GetCurState() == (UINT)ELDERBROTHER::ATTACK)
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

