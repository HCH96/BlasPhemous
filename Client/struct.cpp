#include "pch.h"
#include "struct.h"

#include "CEngine.h"

FSelectGDI::FSelectGDI(HDC _dc, PEN_TYPE _ePenType, BRUSH_TYPE _eBrushType)
	: hCurDC(_dc)
	, hPrevPen(nullptr)
	, hPrevBrush(nullptr)
{
	hPrevPen = (HPEN)SelectObject(_dc, CEngine::GetInst()->GetPEN(_ePenType));

	if (_eBrushType == BRUSH_TYPE::END)
	{
		hPrevBrush = (HBRUSH)SelectObject(_dc, GetStockObject(HOLLOW_BRUSH));
	}
	else
	{
		hPrevBrush = (HBRUSH)SelectObject(_dc, CEngine::GetInst()->GetBRUSH(_eBrushType));
	}

	
	
}

FSelectGDI::FSelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: hCurDC(_dc)
	, hPrevPen(nullptr)
	, hPrevBrush(nullptr)
{
	hPrevBrush = (HBRUSH)SelectObject(_dc, CEngine::GetInst()->GetBRUSH(_eBrushType));
}

FSelectGDI::~FSelectGDI()
{
	SelectObject(hCurDC, hPrevPen);
	SelectObject(hCurDC, hPrevBrush);
}
