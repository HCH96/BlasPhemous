#pragma once
#include "CState.h"
class CPontiffOpening :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPontiffOpening);
    CPontiffOpening();
    ~CPontiffOpening();

};

