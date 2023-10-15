#pragma once

class CEntity;

class CGCMgr
{
	SINGLETON(CGCMgr);

private:
	vector<CEntity*>		m_vecEntity;

public:
	void AddEntity(CEntity* _pEntity) { m_vecEntity.push_back(_pEntity); }


public:
	void tick();

};

