#pragma once
#include "CProjectile.h"


class CMonster;

class CProjectile1 :
    public CProjectile
{
private:
    Vec2    m_vDir;
    CMonster*   m_pTarget;
    float   m_fSpeed;



public:
    virtual void tick(float _DT) override;
    void Targeting();

public:
    CProjectile1();
    ~CProjectile1();

};

