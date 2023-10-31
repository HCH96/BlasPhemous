#pragma once

class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);
private:
	CUI*		m_pFocusedUI;



public:
	void tick();

private:
	CUI* GetPriorityCheck(CUI* _pParentUI);

};

