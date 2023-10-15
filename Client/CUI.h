#pragma once

#include "CObj.h"

class CUI :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    CUI*            m_pParentUI;
    vector<CUI*>    m_vecChildUI;

public:
    void AddChildUI(CUI* _pChildUI)
    {
        if (!IsValid(_pChildUI))
            return;

        m_vecChildUI.push_back(_pChildUI);
        _pChildUI->m_pParentUI = this;
    }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CUI();
    ~CUI();
};

