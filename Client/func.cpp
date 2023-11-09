#include "pch.h"
#include "func.h"

#include "CTaskMgr.h"
#include "CTexture.h"

Vec2 Rotate(Vec2 _vDir, float _angle)
{
	_vDir.Normalize();

	Vec2 vRotateDir = Vec2(cosf(_angle) * _vDir.x - sinf(_angle) * _vDir.y
		, sinf(_angle) * _vDir.x + cosf(_angle) * _vDir.y);

	return vRotateDir;
}

bool GetRotateClock(Vec2 _vDir1, Vec2 _vDir2)
{
	//_vDir1.x; _vDir1.y; 0.f, _vDir1.x; _vDir1.y;
	//_vDir2.x; _vDir2.y; 0.f, _vDir2.x; _vDir2.y;

	if (_vDir1.x * _vDir2.y - _vDir1.y * _vDir2.x > 0.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ChangeLevel(LEVEL_TYPE _eType)
{
	FTask task = {};
	task.Type = TASK_TYPE::LEVEL_CHANGE;
	task.Param_1 = (INT_PTR)_eType;
	CTaskMgr::GetInst()->AddTask(task);
}

void SaveWString(const wstring& _str, FILE* _File)
{
	size_t iLen = _str.length();
	fwrite(&iLen, sizeof(size_t), 1, _File);
	fwrite(_str.c_str(), sizeof(wchar_t), _str.length(), _File);
}

void LoadWString(wstring& _str, FILE* _File)
{
	size_t iLen = 0;
	wchar_t szBuff[255] = {};

	fread(&iLen, sizeof(size_t), 1, _File);
	fread(szBuff, sizeof(wchar_t), iLen, _File);

	_str = szBuff;
}

void AlphaBlendRender(HDC _dc, CTexture* _pTex,Vec2 _vRenderPos, Vec2 _vScale)
{
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc, int(_vRenderPos.x - _vScale.x / 2.f)
		, int(_vRenderPos.y - _vScale.y / 2.f)
		, int(_vScale.x), int(_vScale.y)
		, _pTex->GetDC()
		, 0, 0
		, (int)_pTex->GetWidth(), (int)_pTex->GetHeight()
		, blend);
}

// Bitmap 좌우 반전
HBITMAP FlipBitmapHorizontally(HBITMAP hbm) {
	BITMAP bm;
	GetObject(hbm, sizeof(BITMAP), &bm);
	int wd = bm.bmWidth;
	int hgt = bm.bmHeight;

	HDC hdcScr = GetDC(NULL);
	HDC hdcFlipped = CreateCompatibleDC(hdcScr);
	HBITMAP hbmFlipped = CreateCompatibleBitmap(hdcScr, wd, hgt);
	HGDIOBJ oldFlipped = SelectObject(hdcFlipped, hbmFlipped);
	HDC hdcSrc = CreateCompatibleDC(hdcScr);
	HGDIOBJ oldSrc = SelectObject(hdcSrc, hbm);

	StretchBlt(hdcFlipped, wd, 0, -wd, hgt, hdcSrc, 0, 0, wd, hgt, SRCCOPY);

	SelectObject(hdcSrc, oldSrc);
	DeleteDC(hdcSrc);
	SelectObject(hdcFlipped, oldFlipped);
	DeleteDC(hdcFlipped);
	ReleaseDC(NULL, hdcScr);

	return hbmFlipped;
}

void DrawRotatedRectangle(HDC hdc, int x, int y, int width, int height, float angle) {
	// 회전된 사각형의 꼭짓점 계산
	float radians = angle * (3.14159265358979323846f / 180.0f);
	float cosTheta = cos(radians);
	float sinTheta = sin(radians);

	int x1 = static_cast<int>(x - width / 2 * cosTheta + height / 2 * sinTheta);
	int y1 = static_cast<int>(y - width / 2 * sinTheta - height / 2 * cosTheta);

	int x2 = static_cast<int>(x + width / 2 * cosTheta + height / 2 * sinTheta);
	int y2 = static_cast<int>(y + width / 2 * sinTheta - height / 2 * cosTheta);

	int x3 = static_cast<int>(x + width / 2 * cosTheta - height / 2 * sinTheta);
	int y3 = static_cast<int>(y + width / 2 * sinTheta + height / 2 * cosTheta);

	int x4 = static_cast<int>(x - width / 2 * cosTheta - height / 2 * sinTheta);
	int y4 = static_cast<int>(y - width / 2 * sinTheta + height / 2 * cosTheta);

	// 꼭짓점 좌표를 배열에 저장
	POINT points[4] = { {x1, y1}, {x2, y2}, {x3, y3}, {x4, y4} };

	// 다각형 그리기
	Polygon(hdc, points, 4);
}


