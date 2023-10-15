#include "pch.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CTaskMgr.h"
#include "CCamera.h"
#include "CCollisionMgr.h"
#include "CGCMgr.h"


CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_hDC(nullptr)
	, m_hSubBitMap(nullptr)
	, m_hSubDC(nullptr)
	, m_bDebugRender(true)
{
	// pen, brush 생성
	CreateDefaultGDI();
}

CEngine::~CEngine()
{
	// DC 해제
	ReleaseDC(m_hWnd, m_hDC);

	// SubDC, Bitmap 삭제
	DeleteObject(m_hSubBitMap);
	DeleteDC(m_hSubDC);
	
	// Pen,Brush 삭제
	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}

	for (int i = 0; i < (UINT)BRUSH_TYPE::END; i++)
	{
		DeleteObject(m_arrBrush[i]);
	}

}



void CEngine::init(HWND _hWnd, POINT _ptResolution)
{
	// 멤버 변수 초기화
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	m_hDC = GetDC(m_hWnd);


	// 해상도 변경
	ChangeWindowSize(_ptResolution,false);
	ShowWindow(m_hWnd, true);

	// 추가 비트맵 버퍼
	m_hSubBitMap = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hSubDC = CreateCompatibleDC(m_hDC);
	
	// m_SubDC가 디폴트로 들고있던 비트맵을 삭제
	DeleteObject((HBITMAP)SelectObject(m_hSubDC, m_hSubBitMap));

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CPathMgr::init();
	CLevelMgr::GetInst()->init();
	

}

void CEngine::tick()
{
	// ------------ Manager Update ------------
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	CCamera::GetInst()->tick();
	CLogMgr::GetInst()->tick();

	if (KEY_TAP(KEY::TAB))
	{
		m_bDebugRender ? m_bDebugRender = false : m_bDebugRender = true;
	}


	// ------------ tick ------------
	CLevelMgr::GetInst()->tick();
	CCollisionMgr::GetInst()->tick();


	// ------------ clear -------------
	Clear();


	// ------------ render ------------
	CLevelMgr::GetInst()->render(m_hSubDC);
	CLogMgr::GetInst()->render(m_hSubDC);


	// -------- Task Execute --------
	CTaskMgr::GetInst()->tick();

	// SubDC -> mainDC 복사
	CopyBackBuffer();

	// Garbage Collector tick
	CGCMgr::GetInst()->tick();

}

void CEngine::CreateDefaultGDI()
{
	// red, green, blue blush 생성
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = CreateSolidBrush(RGB(0, 0, 0));


	// red, green, blue pen 생성
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

}

void CEngine::Clear()
{
	Rectangle(m_hSubDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y);
}

void CEngine::CopyBackBuffer()
{
	// m_SubDC -> m_DC 로 복사
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hSubDC, 0, 0, SRCCOPY);
}

void CEngine::ChangeWindowSize(POINT _ptResolution, bool _bMenu)
{
	m_ptResolution = _ptResolution;

	RECT rt = { 0,0,m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
}
