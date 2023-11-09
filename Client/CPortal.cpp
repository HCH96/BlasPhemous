#include "pch.h"
#include "CPortal.h"

#include "CPenitent.h"

CPortal::CPortal()
{
	m_pCollider = AddComponent<CCollider>();
	m_pCollider->SetOffsetPos(Vec2(0.f, 0.f));
}

CPortal::~CPortal()
{
}



void CPortal::begin()
{
	m_pCollider->SetScale(GetScale());
}

void CPortal::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPenitent*>(_OtherObj))
	{
		ChangeLevel(m_eNextLevel);
	}
}

