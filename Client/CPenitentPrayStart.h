#pragma once
#include "CState.h"
class CPenitentPrayStart :
    public CState
{
private:

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentPrayStart);
    CPenitentPrayStart();
    ~CPenitentPrayStart();
};

