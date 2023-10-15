#include "pch.h"
#include "CProjectile1.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"


CProjectile1::CProjectile1()
	: m_vDir{}
	, m_pTarget(nullptr)
	, m_fSpeed(100.f)
{
}

CProjectile1::~CProjectile1()
{
}


void CProjectile1::tick(float _DT)
{
	Targeting();

	Vec2 vPos = GetPos();
	Vec2 vMonPos = m_pTarget->GetPos();

	m_vDir = vMonPos - vPos;

	if (m_vDir.Length() != 0)
	{
		m_vDir.Normalize();
	}

	vPos = vPos + (m_vDir * m_fSpeed *_DT);

	SetPos(vPos);
}

void CProjectile1::Targeting()
{
	Vec2 vPos = GetPos();

	// 가장 가까운 몬스터 찾기
	vector<CMonster*> vecMonster;

	CLevelMgr::GetInst()->GetCurLevel()->GetObjects<CMonster>(vecMonster);

	float min_dis = 9999999.f;

	for (int i = 0; i < vecMonster.size(); ++i)
	{
		Vec2 vMonPos = vecMonster[i]->GetPos();

		Vec2 diff = vPos - vMonPos;

		float dis = diff.Length();

		if (dis < min_dis)
		{
			min_dis = dis;
			m_pTarget = vecMonster[i];
		}
	}
}
