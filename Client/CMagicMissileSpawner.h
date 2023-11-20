#pragma once
#include "CObj.h"

class CMagicMissile;

class CMagicMissileSpawner :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    vector<CMagicMissile*>   m_vecMagicMissile;

    bool m_bIsOn;

    float m_fAcc;
    float m_fLifeTime;
    float m_fCooltime;

    int m_iCurMagic;
    bool m_bDir;
    bool m_bPrevUP;


public:
    void AddMagicMissile(CMagicMissile* _pMagicMissile) { m_vecMagicMissile.push_back(_pMagicMissile); }
    void On(Vec2 _vPos, bool _bDir);
    void Off();

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE_DISABLE(CMagicMissileSpawner);
    CMagicMissileSpawner();
    ~CMagicMissileSpawner();

};

