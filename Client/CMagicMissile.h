#pragma once
#include "CObj.h"

enum class MAGICMISSILE
{
    ACTIVE,
    IMPACT,
};

class CMagicMissile :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CAnimator* m_pAnimator;
    CCollider* m_pCollider;
    MAGICMISSILE m_eState;

    float m_fAccel;
    float m_fVelocity;

    bool m_bIsOn;
    bool m_bDir;


public:
    void On(Vec2 _vPos, bool _bDir);
    void Off();

    bool IsOn() { return m_bIsOn; }


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;


public:
    CLONE_DISABLE(CMagicMissile);
    CMagicMissile();
    ~CMagicMissile();

};

