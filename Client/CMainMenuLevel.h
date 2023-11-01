#pragma once
#include "CLevel.h"

enum class MAIN_MENU
{
    PILGRIMAGE,
    OPTION,
    EXIT,

    END,
};


class CImage;
class CSelectBtn;


class CMainMenuLevel :
    public CLevel
{
private:
    CImage*         m_pCursorImg;
    CSelectBtn*     m_arrBtn[(UINT)MAIN_MENU::END];
    int            m_iCur;

private:
    void ChangeCursorImg();


public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;

public:
    CMainMenuLevel();
    ~CMainMenuLevel();

};

