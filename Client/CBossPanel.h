#pragma once
#include "CUI.h"
class CBossPanel :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:
    CTexture* m_pTexture;

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(CBossPanel);
    CBossPanel();
    ~CBossPanel();

};

