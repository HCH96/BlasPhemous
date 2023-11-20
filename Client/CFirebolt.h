#pragma once
#include "CObj.h"

enum class FIREBOLT
{
    SPAWN,
    ACTIVE,
    IMPACT, 

};

class CFirebolt :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CAnimator* m_pAnimator;
    CCollider* m_pCollider;
    FIREBOLT m_eState;

    float m_fAccel;
    float m_fVelocity;

    bool m_bIsOn;
    Vec2 m_vDir;

public:
    void On(Vec2 _vPos, Vec2 _vDir);
    void Off();

    bool IsOn() { return m_bIsOn; }

    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    virtual void BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol) override;


public:
    CLONE_DISABLE(CFirebolt);
    CFirebolt();
    ~CFirebolt();

};

