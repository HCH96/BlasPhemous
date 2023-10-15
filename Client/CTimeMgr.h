#pragma once
class CTimeMgr
{
	SINGLETON(CTimeMgr);

private:
	LARGE_INTEGER	m_llFrequency;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurCount;

	float			m_fDeltaTime;

	float			m_fTime;
	UINT			m_iCall;

public:
	float GetDeltaTime() { return m_fDeltaTime; }

public:
	void init();
	void tick();

};

