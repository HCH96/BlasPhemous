#pragma once
#include "CLevel.h"
class CStage01_1 :
    public CLevel
{
private:
    bool isEnter;

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

