#pragma once
#include "CUI.h"

class CTexture;

class CPenitentHP :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    CTexture* m_pTexture;

    float       m_fCurHP;
    float       m_fPrevHP;
    float       m_fDecreasingSpeed;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(CPenitentHP);
    CPenitentHP();
    ~CPenitentHP();
};

