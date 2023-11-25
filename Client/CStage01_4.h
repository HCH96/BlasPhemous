#pragma once
#include "CLevel.h"

class CWall;
class CElderShadow;


class CStage01_4 :
    public CLevel
{
private:
    CWall* m_pLeftWall;
    CWall* m_pRightWall;
    CElderShadow* m_pShadow;

public:
    virtual void BossIntro() override;
    virtual void IntroEnd() override;


    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

