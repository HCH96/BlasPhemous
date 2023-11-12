#pragma once
#include "CUI.h"
class CTearsUI :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:
    CTexture*           m_pTexture;
    vector<CTexture*>   m_vecTex;

    float               m_fCur;
    float               m_fRender;
    
    Vec2                m_vNumPos;


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(CTearsUI);
    CTearsUI();
    ~CTearsUI();
};

