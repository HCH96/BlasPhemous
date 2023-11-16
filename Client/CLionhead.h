#pragma once
#include "CObj.h"
class CLionhead :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CStateMachine* m_pAI;
    CAnimator* m_pAnimator;
    CMovement* m_pMovement;
    CCollider* m_pCollider;

    CCollider* m_pHitBox;

    float       m_fHP;


public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void OnHit();

public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;

public:
    CLONE(CLionhead);
    CLionhead();
    CLionhead(const CLionhead& _Origin);
    ~CLionhead();

};

