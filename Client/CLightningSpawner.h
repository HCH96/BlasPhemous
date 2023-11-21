#pragma once
#include "CObj.h"

class CLightning;

class CLightningSpawner :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    vector<CLightning*>   m_vecLightning;
    CObj* m_pTarget;

    bool m_bIsOn;

    float m_fAcc;
    float m_fLifeTime;
    float m_fCooltime;

    int m_iCurLightning;

    int m_iPrevLightnigActive;

public:
    void AddLightning(CLightning* _pLightning) { m_vecLightning.push_back(_pLightning); }
    void On(Vec2 _vPos);
    void Off();

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE_DISABLE(CLightningSpawner);
    CLightningSpawner();
    ~CLightningSpawner();

};

