#pragma once

struct COLLIDER_ID
{
	UINT_PTR	left;
	UINT_PTR	right;

	bool operator < (const COLLIDER_ID& _Other) const
	{
		if (left < _Other.left)
			return true;
		else if (left > _Other.left)
			return false;
		else
		{
			if (right < _Other.right)
				return true;
			else
				return false;
		}
	}
};



class CCollider;

class CCollisionMgr
{
	SINGLETON(CCollisionMgr);

private:
	UINT						m_LayerCheck[(UINT)LAYER::END];
	map<COLLIDER_ID, bool>		m_mapID;

public:
	void tick();
	void CheckCollision(LAYER _eLeft, LAYER _eRight);
	void UnCheck(LAYER _eLeft, LAYER _eRight);

private:
	void CollisionBtwLayer(LAYER _eLeft, LAYER _eRight);
	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);

};
