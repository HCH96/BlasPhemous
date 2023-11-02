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
    CAnimator*              m_pAnimator;
    CCollider*              m_pCollider;
    CMovement*              m_pMovement;
    CStateMachine*          m_pSM;


public:
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

