#pragma once

class CLevel;
class CPenitent;

class CLevelMgr
{
	SINGLETON(CLevelMgr);

private:
	CLevel*			m_pCurLevel;
	CLevel*			m_arrLevels[(UINT)LEVEL_TYPE::END];
	CPenitent*		m_pPenitent;

	UINT			m_iPrevLevel;
	UINT			m_iCurLevel;


public:
	CPenitent* GetPenitent() { return m_pPenitent; }
	CLevel* GetCurLevel() { return m_pCurLevel; }
	UINT GetPrevLevel() { return m_iPrevLevel; }
	
private:
	void ChangeLevel(LEVEL_TYPE _eType);

public:
	void init();
	void tick();
	void render(HDC _dc);

	friend class CTaskMgr;
};

