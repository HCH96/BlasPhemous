#include "pch.h"
#include "CFirebolt.h"


CFirebolt::CFirebolt()
	: m_pAnimator(nullptr)
	, m_pCollider(nullptr)
{

}

CFirebolt::~CFirebolt()
{
}


void CFirebolt::On(Vec2 _vPos, bool _bDir)
{
}

void CFirebolt::Off()
{
}

void CFirebolt::tick(float _DT)
{
}

void CFirebolt::render(HDC _dc)
{
}

void CFirebolt::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
}

