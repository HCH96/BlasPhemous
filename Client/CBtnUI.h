#pragma once
#include "CUI.h"


class CBtnUI :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CBtnUI();
    ~CBtnUI();
};

