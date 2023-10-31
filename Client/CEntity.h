#pragma once

class CEntity
{
private:
	static UINT_PTR g_NextID;

private:
	const UINT_PTR	m_ID;
	wstring			m_strName;
	bool			m_bDead;

public:
	UINT_PTR GetID() { return m_ID; }
	const wstring& GetName() { return m_strName; }
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	bool IsDead() { return m_bDead; }


public:
	virtual CEntity* Clone() = 0;
	CEntity();
	CEntity(const CEntity& _Other);
	virtual ~CEntity();


	friend class CObj;
};

