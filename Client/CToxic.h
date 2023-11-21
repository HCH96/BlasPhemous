#pragma once
#include "CObj.h"

enum class TOXIC
{
    SPAWN,
    ACTIVE,
    IMPACT,
};

class CToxic :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CAnimator* m_pAnimator;
    CCollider* m_pCollider;
    TOXIC m_eState;

    float m_fAccel;
    float m_fVelocity;

    bool m_bIsOn;
    Vec2 m_vDir;


public:
    void On(Vec2 _vPos);
    void Off();

    bool IsOn() { return m_bIsOn; }

    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;


public:
    CLONE_DISABLE(CToxic);
    CToxic();
    ~CToxic();


};

