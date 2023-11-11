#pragma once

#include "CObj.h"

class CUI :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    CUI*            m_pParentUI;
    vector<CUI*>    m_vecChildUI;

    Vec2            m_vFinalPos;

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }

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
    virtual CUI* Clone() = 0;
    CUI();
    CUI(const CUI& _Origin);
    virtual ~CUI();

    friend class CUIMgr;
};

