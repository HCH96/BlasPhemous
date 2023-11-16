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

	bool			m_bDelay;
	float			m_fDelayTime;
	float			m_fDelayAcc;


public:
	float GetDeltaTime() { return m_fDeltaTime; }
	void Delay();


public:
	void init();
	void tick();

};

