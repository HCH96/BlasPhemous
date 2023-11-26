#pragma once
#include "CLevel.h"

class CWall;

class CStage02_2 :
    public CLevel
{
private:
    CWall* m_pLeftWall;
    CWall* m_pRightWall;

public:
    virtual void BossIntro() override;
    virtual void IntroEnd() override;
    virtual void BossDeath() override;


    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

