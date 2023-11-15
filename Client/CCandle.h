#pragma once
#include "CObj.h"

class CAnimator;

class CCandle :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CAnimator* m_pAnimator;

public:
    CLONE(CCandle);
    CCandle(int _Idx);
    CCandle(const CCandle& _Origin);
    ~CCandle();
};

