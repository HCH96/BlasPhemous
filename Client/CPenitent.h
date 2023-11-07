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

    CAnimator*              m_pAnimator;
    CAnimator*              m_pEffector;
    CCollider*              m_pCollider;
    CMovement*              m_pMovement;
    CStateMachine*          m_pSM;

private:
    void AnimationInit();
    void EffectInit();
    void StateInit();

public:
    float GetHP() { return m_fHP; }
    void SetHP(float _f) { m_fHP = _f; }

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

