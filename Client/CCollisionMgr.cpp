#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CLevelMgr.h"

#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_LayerCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::ClearIDMap()
{
	map<COLLIDER_ID, bool>::iterator iter = m_mapID.begin();

	for (; iter != m_mapID.end(); ++iter)
	{
		iter->second = false;
	}


}

void CCollisionMgr::tick()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (UINT iRow = 0; iRow < 32; ++iRow)
	{
		for (UINT iCol = iRow; iCol < 32; ++iCol)
		{
			if (!(m_LayerCheck[iRow] & (1 << iCol)))
				continue;

			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}
}

void CCollisionMgr::CheckCollision(LAYER _eLeft, LAYER _eRight)
{
	int iRow = 0, iCol = 0;
	if ((UINT)_eLeft < (UINT)_eRight)
	{
		iRow = (int)_eLeft;
		iCol = (int)_eRight;
	}
	else
	{
		iRow = (int)_eRight;
		iCol = (int)_eLeft;
	}

	m_LayerCheck[iRow] |= (1 << iCol);

}

void CCollisionMgr::UnCheck(LAYER _eLeft, LAYER _eRight)
{
	int iRow = 0, iCol = 0;
	if ((UINT)_eLeft < (UINT)_eRight)
	{
		iRow = (int)_eLeft;
		iCol = (int)_eRight;
	}
	else
	{
		iRow = (int)_eRight;
		iCol = (int)_eLeft;
	}

	m_LayerCheck[iRow] &= ~(1 << iCol);


}

void CCollisionMgr::CollisionBtwLayer(LAYER _eLeft, LAYER _eRight)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if (pCurLevel == nullptr)
		return;

	const vector<CCollider*>& vecLeft = pCurLevel->GetLayer((int)_eLeft)->GetColliders();
	const vector<CCollider*>& vecRight = pCurLevel->GetLayer((int)_eRight)->GetColliders();

	if (_eLeft != _eRight)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				COLLIDER_ID ID = { vecLeft[i]->GetID(), vecRight[j]->GetID() };

				map<COLLIDER_ID, bool>::iterator iter = m_mapID.find(ID);

				if (m_mapID.end() == iter)
				{
					m_mapID.insert(make_pair(ID, false));
					iter = m_mapID.find(ID);
				}

				// 충돌 발생
				if (IsCollision(vecLeft[i], vecRight[j]))
				{
					// 이전 프레임에 충돌하지 않았을 때
					if (false == iter->second)
					{
						// Collider의 오브젝트가 살아있고, Collider가 On일 때
						if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead() && !vecLeft[i]->IsOff() && !vecRight[j]->IsOff())
						{
							vecLeft[i]->BeginOverlap(vecRight[j]);
							vecRight[j]->BeginOverlap(vecLeft[i]);
						}

						iter->second = true;

					}
					// 이전 프레임에 충돌했었을 때
					else
					{
						// Collider의 오브젝트가 살아있고, Collider가 On일 때
						if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead() && !vecLeft[i]->IsOff() && !vecRight[j]->IsOff())
						{
							vecLeft[i]->Overlap(vecRight[j]);
							vecRight[j]->Overlap(vecLeft[i]);
						}
						else
						{
							vecLeft[i]->EndOverlap(vecRight[j]);
							vecRight[j]->EndOverlap(vecLeft[i]);
							iter->second = false;
						}
					}
				}
				// 충돌 발생 x
				else
				{
					// 이전 프레임에 충돌 했을 때
					if (iter->second)
					{
						vecLeft[i]->EndOverlap(vecRight[j]);
						vecRight[j]->EndOverlap(vecLeft[i]);
					}
					iter->second = false;
				}
			}
		}
	}


}

bool CheckShaft(Vec2 _NorVec, Vec2 _vAxis, CCollider* _pLeft, CCollider* _pRight)
{
	// 축 기준 내적 거리
	float fDistance = abs(_vAxis.Dot(_NorVec));

	// Box 1
	Vec2 vLColScale = _pLeft->GetScale();

	// Box 2
	Vec2 vRColScale = _pRight->GetScale();

	Vec2 vLColUp = Vec2(0.f, 1.f).Rotate(_pLeft->GetAngle());
	Vec2 vLColRight = Vec2(1.f, 0.f).Rotate(_pLeft->GetAngle());

	Vec2 vRColUp = Vec2(0.f, 1.f).Rotate(_pRight->GetAngle());
	Vec2 vRColRight = Vec2(1.f, 0.f).Rotate(_pRight->GetAngle());

	if (fDistance > abs(_vAxis.Dot(vLColUp * vLColScale.y / 2.f) )
		+ abs(_vAxis.Dot(vLColRight * vLColScale.x / 2.f) )
		+ abs(_vAxis.Dot(vRColUp * vRColScale.y / 2.f) )
		+ abs(_vAxis.Dot(vRColRight * vRColScale.x / 2.f)) )
	{
		return false;
	}

	return true;
}

bool CCollisionMgr::IsCollision(CCollider* _pLeft, CCollider* _pRight)
{
	Vec2 vLColUp = Vec2(0.f, 1.f).Rotate(_pLeft->GetAngle());
	Vec2 vLColRight = Vec2(1.f, 0.f).Rotate(_pLeft->GetAngle());

	Vec2 vRColUp = Vec2(0.f, 1.f).Rotate(_pRight->GetAngle());
	Vec2 vRColRight = Vec2(1.f, 0.f).Rotate(_pRight->GetAngle());


	Vec2 vNorVec = _pLeft->GetPos() - _pRight->GetPos();

	// 모든 법선벡터를 한번씩 축으로 검사 진행
	if (!CheckShaft(vNorVec, vLColUp, _pLeft, _pRight))
		return false;
	if (!CheckShaft(vNorVec, vLColRight, _pLeft, _pRight))
		return false;
	if (!CheckShaft(vNorVec, vRColUp, _pLeft, _pRight))
		return false;
	if (!CheckShaft(vNorVec, vRColRight, _pLeft, _pRight))
		return false;


	return true;
}

