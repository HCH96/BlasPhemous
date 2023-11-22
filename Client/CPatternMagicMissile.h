#pragma once
#include "CState.h"
class CPatternMagicMissile :
    public CState
{
private:
    float m_fAcc;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPatternMagicMissile);
    CPatternMagicMissile();
    ~CPatternMagicMissile();

};

