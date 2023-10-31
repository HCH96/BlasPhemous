#pragma once

class CTexture;

class CEngine
{
	SINGLETON(CEngine);

private:
	HWND		m_hWnd;				// ���� ������ �ڵ�
	POINT		m_ptResolution;		// ������ �ػ� ����
	HDC			m_hDC;				// ���� DC

	CTexture*	m_pSubTex;			// SubBuffer Texture;

	bool		m_bDebugRender;		// Debug render

	// ���� ����� pen, brush
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];

private:
	void CreateDefaultGDI();
	void Clear();
	void CopyBackBuffer();

public:
	HWND GetMainWind() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }


	HPEN GetPEN(PEN_TYPE _ePenType) { return m_arrPen[(UINT)_ePenType]; }
	HBRUSH GetBRUSH(BRUSH_TYPE _eBrushType) { return m_arrBrush[(UINT)_eBrushType]; }

public:
	void ChangeWindowSize(POINT _ptResolution, bool _bMenu);
	bool DebugRender() { return m_bDebugRender; }


public:
	void init(HWND _hWnd, POINT _ptResolution);
	void tick();
};

