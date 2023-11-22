#pragma once
#include "CObj.h"
class CMagicMissile;

class CMagicMissileSpawner2 :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    vector<CMagicMissile*>   m_vecMagicMissile;

    bool m_bIsOn;




public:
    void AddMagicMissile(CMagicMissile* _pMagicMissile) { m_vecMagicMissile.push_back(_pMagicMissile); }
    void On(Vec2 _vPos);
    void Off();

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    CLONE_DISABLE(CMagicMissileSpawner2);
    CMagicMissileSpawner2();
    ~CMagicMissileSpawner2();

};

