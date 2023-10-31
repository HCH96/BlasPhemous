#pragma once
#include "CUI.h"

class CTexture;

typedef void(*BtnCallBack)(void);
typedef void(CEntity::* DelegateFunc)(void);

class CBtnUI :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    CTexture*       m_pNormalImg;
    CTexture*       m_pHoverImg;
    CTexture*       m_pPressedImg;
    CTexture*       m_pCurImg;

    // 전역함수 포인터
    BtnCallBack     m_pCallBackFunc;

    // 델리게이트 (멤버함수 포인터)
    CEntity*        m_pInst;
    DelegateFunc    m_pDelegate;

    Vec2            m_vLBtnDownPos;

public:
    void SetNormalImg(CTexture* _pNormalImg) { m_pNormalImg = _pNormalImg; }
    void SetPressedImg(CTexture* _pPressedImg) { m_pPressedImg = _pPressedImg; }
    void SetHoverImg(CTexture* _pHoverImg) { m_pHoverImg = _pHoverImg; }

    void SetCallBack(BtnCallBack _CallBack) { m_pCallBackFunc = _CallBack; }
    void SetDelegate(CEntity* _Inst, DelegateFunc _Func) { m_pInst = _Inst; m_pDelegate = _Func; }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void OnHovered(Vec2 _vMousePos) override;
    virtual void OnUnHovered(Vec2 _vMousePos) override;
    virtual void MouseOn(Vec2 _vMousePos) override;

    virtual void LBtnDown(Vec2 _vMousePos) override;
    virtual void LBtnUp(Vec2 _vMousePos) override;
    virtual void LBtnClicked(Vec2 _vMousePos) override;


public:
    CLONE(CBtnUI);
    CBtnUI();
    ~CBtnUI();
};

