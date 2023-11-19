#pragma once
#include "CObj.h"
class CElderBrother :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CAnimator* m_pAnimator;
    CCollider* m_pCollider;
    CMovement* m_pMovement;
    CStateMachine* m_pAI;

    float       m_fHP;

public:
    float GetHP() { return m_fHP; }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void OnHit();

public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;

    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;

public:
    CLONE_DISABLE(CElderBrother);
    CElderBrother();
    ~CElderBrother();

};

