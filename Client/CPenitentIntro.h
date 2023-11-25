#pragma once
#include "CState.h"
class CPenitentIntro :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPenitentIntro);
    CPenitentIntro();
    ~CPenitentIntro();

};

