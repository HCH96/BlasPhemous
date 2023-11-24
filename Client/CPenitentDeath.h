#pragma once
#include "CState.h"
class CPenitentDeath :
    public CState
{
private:
    bool SoundPlay;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentDeath);
    CPenitentDeath();
    ~CPenitentDeath();

};

