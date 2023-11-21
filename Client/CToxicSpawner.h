#pragma once
#include "CObj.h"

class CToxic;

class CToxicSpawner :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    vector<CToxic*>   m_vecCToxic;

    bool m_bIsOn;

    float m_fAcc;
    float m_fLifeTime;
    float m_fCooltime;

    int m_iCurToxic;

public:
    void AddToxic(CToxic* _pToxic) { m_vecCToxic.push_back(_pToxic); }
    void On(Vec2 _vPos);
    void Off();

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE_DISABLE(CToxicSpawner);
    CToxicSpawner();
    ~CToxicSpawner();

};

