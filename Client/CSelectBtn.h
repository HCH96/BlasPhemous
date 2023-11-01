#pragma once
#include "CUI.h"


class CTexture;

typedef void(*BtnCallBack)(void);
typedef void(CEntity::* DelegateFunc)(void);

class CSelectBtn :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    CTexture*   m_pNormalImg;
    CTexture*   m_pSelectImg;
    bool        m_bSelect;


    // 전역함수 포인터
    BtnCallBack     m_pCallBackFunc;

    // 델리게이트 (멤버함수 포인터)
    CEntity* m_pInst;
    DelegateFunc    m_pDelegate;

public:
    bool GetSelect() { return m_bSelect; }
    void SetSelect(bool _b) { m_bSelect = _b; }

    void SetNormalImg(CTexture* _pNormalImg) { m_pNormalImg = _pNormalImg; }
    void SetNormalImg(const wstring& _strKey);
    void SetSelectImg(const wstring& _strKey);

    void SetCallBack(BtnCallBack _CallBack) { m_pCallBackFunc = _CallBack; }
    void SetDelegate(CEntity* _Inst, DelegateFunc _Func) { m_pInst = _Inst; m_pDelegate = _Func; }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void Select();


public:
    CLONE(CSelectBtn);
    CSelectBtn();
    ~CSelectBtn();
};

