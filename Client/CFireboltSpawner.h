#pragma once
#include "CObj.h"

class CFirebolt;

class CFireboltSpawner :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    vector<CFirebolt*>   m_vecFirebolt;
    CObj*               m_pTarget;


    bool m_bIsOn;

    float m_fAcc;
    float m_fLifeTime;
    float m_fCooltime;

    int m_iCurFire;

public:
    void AddFirebolt(CFirebolt* _pFirebolt) { m_vecFirebolt.push_back(_pFirebolt); }
    void On(Vec2 _vPos);
    void Off();

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE_DISABLE(CFireboltSpawner);
    CFireboltSpawner();
    ~CFireboltSpawner();

};

