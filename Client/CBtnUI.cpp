#include "pch.h"
#include "CBtnUI.h"

#include "resource.h"
#include "CEngine.h"

#include "CKeyMgr.h"

CBtnUI::CBtnUI()
	: m_pNormalImg(nullptr)
	, m_pPressedImg(nullptr)
	, m_pHoverImg(nullptr)
	, m_pCurImg(nullptr)
	, m_pCallBackFunc(nullptr)
	, m_pInst(nullptr)
	, m_pDelegate(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::tick(float _DT)
{



	// component tick -> ChildUI tick
	Super::tick(_DT);
}

void CBtnUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if( nullptr != m_pCurImg)
	{
	}
	else
	{
		Rectangle(_dc, (int)vPos.x, (int)vPos.y, int(vPos.x + vScale.x), int(vPos.y + vScale.y));
	}


	// 부모클래스(CUI) 렌더함수 호출(자식 UI 들한테 render 를 호출한다)
	// Component render -> ChildUI render
	Super::render(_dc);

}

void CBtnUI::OnHovered(Vec2 _vMousePos)
{
	m_pCurImg = m_pHoverImg;
}

void CBtnUI::MouseOn(Vec2 _vMousePos)
{
}

void CBtnUI::OnUnHovered(Vec2 _vMousePos)
{
	m_pCurImg = m_pNormalImg;
}



void CBtnUI::LBtnDown(Vec2 _vMousePos)
{
	m_pCurImg = m_pPressedImg;
}

void CBtnUI::LBtnUp(Vec2 _vMousePos)
{
	m_pCurImg = m_pNormalImg;
}

INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void CBtnUI::LBtnClicked(Vec2 _vMousePos)
{
	if (nullptr != m_pCallBackFunc)
	{
		m_pCallBackFunc();
	}

	if (nullptr != m_pInst && nullptr != m_pDelegate)
	{
		(m_pInst->*m_pDelegate)();
	}
}

