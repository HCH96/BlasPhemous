#pragma once
#include "CState.h"
class CPopeNone :
    public CState
{
public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPopeNone);
    CPopeNone();
    ~CPopeNone();

};

