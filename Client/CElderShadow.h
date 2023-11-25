#pragma once
#include "CObj.h"
class CElderShadow :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CAnimator* m_pAnimator;
    CStateMachine* m_pAI;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(CElderShadow);
    CElderShadow();
    ~CElderShadow();

};

