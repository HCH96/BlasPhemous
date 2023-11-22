#pragma once
#include "CObj.h"

class CLightning;

class CLightningSpawner2 :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    vector<CLightning*>   m_vecLightning;

    bool m_bIsOn;

    float m_fAcc;
    float m_fLifeTime;
    float m_fCooltime;

    bool m_bDir;

    int m_iCurLightning;
        
public:
    void AddLightning(CLightning* _pLightning) { m_vecLightning.push_back(_pLightning); }
    void On(Vec2 _vPos, bool _bDir);
    void Off();

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE_DISABLE(CLightningSpawner2);
    CLightningSpawner2();
    ~CLightningSpawner2();

};

