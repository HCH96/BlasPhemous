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

    CAnimator*              m_pAnimator;
    CAnimator*              m_pEffector;
    CAnimator*              m_pDustAnimator;
    CCollider*              m_pCollider;
    CMovement*              m_pMovement;
    CStateMachine*          m_pSM;

private:
    void AnimationInit();
    void EffectInit();
    void DustAnimInit();
    void StateInit();

public:
    float GetHP() { return m_fHP; }
    int GetMP() { return m_iMP; }
    int GetPotionCount() { return m_iPotion; }
    float GetTears() { return m_fTears; }
    
    void SetHP(float _f) { m_fHP = _f; }
    void SetMP(float _f) { m_fHP = _f; }
    void SetPotionCount(int _iCount) { m_iPotion = _iCount; }
    void SetTears(int _i) { m_fTears = _i; }

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

