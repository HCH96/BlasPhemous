#pragma once
#include "CObj.h"

class CRayBeam;

class CSpawner :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CCollider* m_pCollider;
    CMovement* m_pMovement;

    vector<CRayBeam*> m_vecRayBeam;

    bool m_bIsOn;
    bool m_bDir;

    float m_fAcc;
    float m_fLifeTime;
    float m_fCooltime;

    int m_iCurRay;

public:
    void AddRay(CRayBeam* _pRayBeam) { m_vecRayBeam.push_back(_pRayBeam); }
    void On(Vec2 _vPos, bool _bDir);
    void Off();

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE_DISABLE(CSpawner);
    CSpawner();
    ~CSpawner();
};

