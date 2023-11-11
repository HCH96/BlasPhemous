#pragma once
#include "CUI.h"

class CPenitentMP :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    CTexture* m_pTexture;


    vector<float> m_vecMPIdx;
    float       m_fCurMP;
    float       m_fPrevMP;
    float       m_fDecreasingSpeed;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(CPenitentMP);
    CPenitentMP();
    ~CPenitentMP();
};

