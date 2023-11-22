#pragma once
#include "CState.h"
class CPatternFirebolt :
    public CState
{
private:
    float m_fAcc;
    int m_iCurSpawner;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPatternFirebolt);
    CPatternFirebolt();
    ~CPatternFirebolt();

};

