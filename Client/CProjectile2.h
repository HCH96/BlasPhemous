#pragma once
#include "CProjectile.h"


class CMonster;

class CProjectile2 :
    public CProjectile
{
private:
    CMonster*   m_pTarget;

    Vec2    m_vVelocity;
    Vec2    m_vAccel;

    float   m_fMass;

    float   m_fForce;


public:
    virtual void tick(float _DT) override;
    void Targeting();


public:
    CProjectile2();
    ~CProjectile2();

};

