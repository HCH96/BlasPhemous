#pragma once
#include "CLevel.h"
class CStage03_3 :
    public CLevel
{
public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

