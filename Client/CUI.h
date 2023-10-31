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

    bool            m_bMouseOn;
    bool            m_bMouseOn_Prev;
    bool            m_bMouseLBtnDown;

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    bool IsLBtnDown() { return m_bMouseLBtnDown; }

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
    virtual void OnHovered(Vec2 _vMousePos) {}
    virtual void MouseOn(Vec2 _vMousePos) {}
    virtual void OnUnHovered(Vec2 _vMousePos) {}

    virtual void LBtnDown(Vec2 _vMousePos) {}
    virtual void LBtnUp(Vec2 _vMousePos) {}
    virtual void LBtnClicked(Vec2 _vMousePos) {}

public:
    virtual CUI* Clone() = 0;
    CUI();
    CUI(const CUI& _Origin);
    virtual ~CUI();

    friend class CUIMgr;
};

