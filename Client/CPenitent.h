#pragma once
#include "CObj.h"

class CAnimator;
class CStateMachine;
class CCollider;
class CMovement;


class CPenitent :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    float                   m_fHP;
    int                     m_iMP;
    int                     m_iPotion;
    float                   m_fTears;
    int                     m_iOverlapGround;
    bool                    m_bIsLeft;
    bool                    m_bDownPlatform;

    bool                    m_bIsHit;
    float                   m_fHitTimer;

    int                    m_iParrySucces;

    UINT                    m_iCheckPoint;

    CAnimator*              m_pAnimator;
    CAnimator*              m_pEffector;
    CAnimator*              m_pDustAnimator;
    CCollider*              m_pCollider;
    CCollider*              m_pHitBox;
    CMovement*              m_pMovement;
    CStateMachine*          m_pSM;

private:
    void AnimationInit();
    void EffectInit();
    void DustAnimInit();
    void StateInit();

public:
    void SetParry(int _i) { m_iParrySucces = _i; }
    int GetParry() { return m_iParrySucces; }
    void OnDamaged();
    void OnHit();
    void SetHit(bool _b) { m_bIsHit = _b; }

public:
    float GetHP() { return m_fHP; }
    int GetMP() { return m_iMP; }
    int GetPotionCount() { return m_iPotion; }
    float GetTears() { return m_fTears; }
    bool GetIsLeft() { return m_bIsLeft; }
    bool GetDownPlatform() { return m_bDownPlatform; }
    UINT GetState() { return m_pSM->GetCurState(); }
    int GetOverlapGround() { return m_iOverlapGround; }
    
    void SetHP(float _f) { m_fHP = _f; }
    void SetMP(int _i) { m_iMP = _i; }
    void SetPotionCount(int _iCount) { m_iPotion = _iCount; }
    void SetTears(int _i) { m_fTears = (float)_i; }
    void SetLeft(bool _b) { m_bIsLeft = _b; }
    void SetDownPlatform(bool _b) { m_bDownPlatform = _b; }

    void SetState(PENITENT_STATE _eSTATE) { m_pSM->ChangeState((UINT)_eSTATE); }
    void SetCheckPoint(UINT _iCheckPoint) { m_iCheckPoint = _iCheckPoint; }

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;

public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CPenitent);
    CPenitent();
    CPenitent(const CPenitent& _Origin);
    ~CPenitent();

};

