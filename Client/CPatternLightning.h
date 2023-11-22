#pragma once
#include "CState.h"
class CPatternLightning :
    public CState
{
private:
    float m_fAcc;

    int m_iCount;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPatternLightning);
    CPatternLightning();
    ~CPatternLightning();

};

