#pragma once
#include "CObj.h"
class CShieldMaiden :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CStateMachine* m_pAI;
    CAnimator* m_pAnimator;
    CAnimator* m_pEffector;
    CMovement* m_pMovement;
    CCollider* m_pCollider;

    CCollider* m_pHitBox;

    float       m_fHP;
    bool        m_bIsBlock;
    bool        m_bStateBlock;


public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void OnHit();
    void SetBlock(bool _b) { m_bIsBlock = _b; }
    bool GetBlock() { return m_bIsBlock; }

    void SetStateBlock(bool _b) { m_bStateBlock = _b; }
    bool GetStateBlock() { return m_bStateBlock; }


public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;

public:
    CLONE(CShieldMaiden);
    CShieldMaiden();
    CShieldMaiden(const CShieldMaiden& _Origin);
    ~CShieldMaiden();
};

