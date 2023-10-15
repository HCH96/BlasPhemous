#include "pch.h"
#include "CProjectile3.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"

CProjectile3::CProjectile3()
	: m_vDir{0.f,-1.f}
	, m_pTarget(nullptr)
	, m_fSpeed(80.f)
	, m_fTheta(0.f)
	, m_vDiff{}
{
}

CProjectile3::~CProjectile3()
{
}



void CProjectile3::tick(float _DT)
{
	Targeting();

	Vec2 vPos = GetPos();
	Vec2 vMonPos = m_pTarget->GetPos();

	m_vDiff = vMonPos - vPos;
	m_vDiff.Normalize();
	m_vDir.Normalize();

	// ���� ����
	AdjustDir(_DT);

	// �̵�
	m_vDir.Normalize();

	vPos.x = vPos.x + m_vDir.x * m_fSpeed * _DT;
	vPos.y = vPos.y + m_vDir.y * m_fSpeed * _DT;
	
	SetPos(vPos);
}

void CProjectile3::AdjustDir(float _DT)
{
	// m_vDiff�� m_vDir�� ���̰� ���ϱ�
	float dot = m_vDiff.x * m_vDir.x + m_vDiff.y * m_vDir.y;

	m_fTheta = acosf(dot / m_vDiff.Length() * m_vDir.Length());


	// 180���� �Ѿ���� üũ
	// sub�� m_vDiff�� 90�� �̸��̶�� m_vDiff�� m_vDir�� ������ 0~180�� �ƴ϶�� 180~360��
	Vec2 Sub = m_vDir.Rotate(90 * PI / 180);
	Sub.Normalize();

	float dotSub = m_vDiff.x * Sub.x + m_vDiff.y * Sub.y;
	float dotTheta = acosf(dotSub / m_vDiff.Length() * Sub.Length());

	if (dotTheta > 1.5708)
	{
		m_fTheta = -m_fTheta;
	}


	// m_vDir��  m_fTheta��ŭ ȸ��
	m_vDir = m_vDir.Rotate(m_fTheta*_DT);


}

void CProjectile3::Targeting()
{
	Vec2 vPos = GetPos();

	// ���� ����� ���� ã��
	vector<CMonster*> vecMonster;

	CLevelMgr::GetInst()->GetCurLevel()->GetObjects(vecMonster);


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


