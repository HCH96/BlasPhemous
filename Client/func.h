#pragma once

class CTexture;


Vec2 Rotate(Vec2 _vDir, float _angle);
bool GetRotateClock(Vec2 _vDir1, Vec2 _vDir2);

template <typename T>
bool IsValid(T*& _pEntity)
{
	if (_pEntity == nullptr)
	{
		return false;
	}

	if (_pEntity->IsDead())
	{
		_pEntity = nullptr;
		return false;
	}

	return true;
}

void ChangeLevel(LEVEL_TYPE _eType);

void SaveWString(const wstring& _str, FILE* _File);
void LoadWString(wstring& _str, FILE* _File);

void AlphaBlendRender(HDC _dc, CTexture* _pTex, Vec2 _vRenderPos, Vec2 _vScale);
HBITMAP FlipBitmapHorizontally(HBITMAP hbm);

void DrawRotatedRectangle(HDC hdc, int x, int y, int width, int height, float angle);

// 선형 보간 함수
float lerp(float a, float b, float t);

float DegreeToRadian(float _fDegree);

float VecToRadian(Vec2 _vDir);

float RadiansToDegrees(float radians);