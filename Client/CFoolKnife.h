#pragma once
#include "CObj.h"
class CFoolKnife :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CStateMachine* m_pAI;
    CAnimator* m_pAnimator;
    CMovement* m_pMovement;
    CCollider* m_pCollider;

    float       m_fHP;


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void OnHit();

public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;

public:
    CLONE(CFoolKnife);
    CFoolKnife();
    CFoolKnife(const CFoolKnife& _Origin);
    ~CFoolKnife();


};

