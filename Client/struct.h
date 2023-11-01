#pragma once

struct Vec2
{
public:
	float		x;
	float		y;


public:
	// 생성자

	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(UINT _x, UINT _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

public:
	// 함수
	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	float Distance(Vec2 _Other)
	{
		return sqrtf(powf(x - _Other.x, 2) + powf(y - _Other.y, 2));
	}

	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

	Vec2& Normalize()
	{
		float fLen = Length();

		if (fLen == 0.f)
			return *this;

		x /= fLen;
		y /= fLen;

		return *this;
	}

	Vec2 Rotate(float _fTheta)
	{
		Vec2 tmp;

		tmp.x = x * cosf(_fTheta) - y * sinf(_fTheta);
		tmp.y = x * sinf(_fTheta) + y * cosf(_fTheta);

		return tmp;
	}


public:
	// 오퍼레이터

	Vec2 operator - ()
	{
		return Vec2(-x, -y);
	}

	Vec2 operator + (float _f) const
	{
		return Vec2(x + _f, y + _f);
	}

	Vec2 operator - (float _f) const
	{
		return Vec2(x - _f, y - _f);
	}

	Vec2 operator * (float _f) const
	{
		return Vec2(x * _f, y * _f);
	}

	Vec2 operator / (float _f) const
	{

		assert(_f != 0);
		return Vec2(x / _f, y / _f);
	}

	Vec2& operator +=(float _f)
	{
		x += _f;
		y += _f;

		return *this;
	}

	Vec2& operator -=(float _f)
	{
		x -= _f;
		y -= _f;

		return *this;
	}

	Vec2& operator *=(float _f)
	{
		x *= _f;
		y *= _f;

		return *this;
	}

	Vec2& operator /=(float _f)
	{
		assert(_f != 0);

		x /= _f;
		y /= _f;

		return *this;
	}

	Vec2 operator + (const Vec2& _Other) const
	{
		return Vec2(x + _Other.x, y + _Other.y);
	}

	Vec2 operator - (const Vec2& _Other) const
	{
		return Vec2(x - _Other.x, y - _Other.y);
	}

	Vec2 operator * (const Vec2& _Other) const
	{
		return Vec2(x * _Other.x, y * _Other.y);
	}

	Vec2 operator / (const Vec2& _Other) const
	{
		if (_Other.x == 0 || _Other.y == 0)
		{
			return *this;
		}

		assert(_Other.x != 0 && _Other.y != 0);
		return Vec2(x / _Other.x, y / _Other.y);
	}


	Vec2& operator +=(const Vec2& _Other)
	{
		x += _Other.x;
		y += _Other.y;

		return *this;
	}

	Vec2& operator -=(const Vec2& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;

		return *this;
	}

	Vec2& operator *=(const Vec2& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;

		return *this;
	}

	Vec2& operator /=(const Vec2& _Other)
	{
		if (_Other.x == 0 || _Other.y == 0)
		{
			return *this;
		}

		assert(_Other.x != 0 && _Other.y != 0);

		x /= _Other.x;
		y /= _Other.y;

		return *this;
	}
};


struct FKeyData
{
	KEY			eKey;
	KEY_STATE	eState;
	bool		bPressed;
};

struct FMonInfo
{
	wchar_t szName[50];
	float HP;
	float MP;
	float Att;
	float Int;
	float Speed;
};

struct FTask
{
	TASK_TYPE Type;
	UINT_PTR Param_1;
	UINT_PTR Param_2;
};

struct FSelectGDI
{
	HDC		hCurDC;
	HPEN	hPrevPen;
	HBRUSH	hPrevBrush;

	FSelectGDI(HDC _dc, PEN_TYPE _ePenType, BRUSH_TYPE _eBrushType = BRUSH_TYPE::END);
	FSelectGDI(HDC _dc, BRUSH_TYPE _eBrushType);
	FSelectGDI(const FSelectGDI& _Other) = delete;
	~FSelectGDI();
};

struct FLog
{
	LOG_LEVEL		Level;
	wstring			Message;
	float			AccTime;
};