#pragma once
#include "CUI.h"
class CBossPanel :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:
    CTexture* m_pTexture;
    CTexture* m_pName;
    bool m_bOn;

public:
    void SetTexture(CTexture* _pTexture) { m_pName = _pTexture; }

    void On() { m_bOn = true; }
    void Off() { m_bOn = false; }

    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(CBossPanel);
    CBossPanel();
    ~CBossPanel();

};

