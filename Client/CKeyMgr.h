#pragma once

// TAP, PRESSED, RELEASED, NONE

class CKeyMgr
{
	SINGLETON(CKeyMgr);
private:
	vector<FKeyData>	m_vecKeyData;
	Vec2				m_vMousePos;

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKeyData[(UINT)_eKey].eState; }
	Vec2 GetMousePos() { return m_vMousePos; }

public:
	void init();
	void tick();

};

