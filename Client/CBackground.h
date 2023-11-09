#pragma once
#include "CObj.h"

class CTexture;

class CBackground :
    public CObj
{
private:
	CTexture*			m_pTex;
	Vec2				m_vParallaxSpeed;

public:
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
	void SetParallaxSpeed(Vec2 _v) { m_vParallaxSpeed = _v; }

public:
	virtual void tick(float _DT);
	virtual void render(HDC _dc);

public:
	CLONE_DISABLE(CBackground);
	CBackground();
	CBackground(const CBackground& _Origin) = delete;
	~CBackground();

};

