#pragma once
#include "CUI.h"

class CTextrue;

class CPanelUI :
    public CUI
{
    GENERATED_OBJECT(CUI);


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CPanelUI);
    CPanelUI();
    ~CPanelUI();
};

