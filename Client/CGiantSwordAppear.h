#pragma once
#include "CState.h"
class CGiantSwordAppear :
    public CState
{

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CGiantSwordAppear);
    CGiantSwordAppear();
    ~CGiantSwordAppear();


};

