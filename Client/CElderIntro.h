#pragma once
#include "CState.h"
class CElderIntro :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElderIntro);
    CElderIntro();
    ~CElderIntro();

};

