#pragma once
#include "CState.h"
class CElderShdowNone :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElderShdowNone);
    CElderShdowNone();
    ~CElderShdowNone();

};

