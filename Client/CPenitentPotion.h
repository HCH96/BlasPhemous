#pragma once
#include "CUI.h"

class CTexture;

class CPenitentPotion :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:
    CTexture*   m_pFullPotion;
    CTexture*   m_pEmptyPotion;

    int     m_iCount;
    int     m_iCur;
    int     m_iInterval;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(CPenitentPotion);
    CPenitentPotion();
    ~CPenitentPotion();

};

