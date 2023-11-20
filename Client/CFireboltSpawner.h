#pragma once
#include "CObj.h"

class Firebolt;

class CFireboltSpawner :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:

    vector<Firebolt*> m_vecFirebolt;

    bool m_bIsOn;

    float m_fAcc;
    float m_fLifeTime;
    float m_fCooltime;

    int m_iCurFire;

public:
    void AddRay(Firebolt* _pRayBeam) { m_vecFirebolt.push_back(_pRayBeam); }
    void On(Vec2 _vPos, bool _bDir);
    void Off();

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE_DISABLE(CFireboltSpawner);
    CFireboltSpawner();
    ~CFireboltSpawner();

};

