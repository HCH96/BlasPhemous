#pragma once
#include "CUI.h"

class CPanelUI :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CPanelUI();
    ~CPanelUI();
};

