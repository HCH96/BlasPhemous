#pragma once

class CTexture;
class CObj;

typedef void(*EffectCallBack)(LEVEL_TYPE _eLevelType);

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	SHAKE,
	DEATH,
	BOSS_CLEAR,
};

struct FCamEvent
{
	CAM_EFFECT	Type;
	float		AccTime;
	float		Duration;
	LEVEL_TYPE	NextLevel;
};

class CCamera
{
	SINGLETON(CCamera);

private:

	Vec2		m_vPrevLookAt;	// 카메라가 직전 프레임에 보고 있던 지점
	Vec2		m_vCurLookAt;	// 카메라가 지금 보고있는 지점
	Vec2		m_vLookAt;		// 카메라가 바라봐야할 지점
	Vec2		m_vDiff;		// realPos와 renderPos 차이

	Vec2		m_vCameraLimitLT;
	Vec2		m_vCameraLimit; // 카메라가 바라볼 수 있는 제한 지점
	Vec2		m_vLookAtOffset;// 카메라가 바라봐야할 지점의 오프셋
	float		m_fSpeed;		// 타겟을 따라가는 속도


	float		m_fShakeIntensity; // 카메라를 흔드는 강도
	Vec2		m_vTarget;	   // 카메라가 흔들릴 때 도착 좌표


	bool		m_bInEvent;
	bool		m_bInClear;


	CTexture* m_pVeil;
	CTexture* m_pDeathScreen;
	CTexture* m_pBossClear;
	CObj* m_pTarget;


	list<FCamEvent>		m_EventList;
	UINT				m_Alpha;

public:
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
	Vec2 GetCurLookAt() { return m_vCurLookAt; }
	int GetEventCount() { return (int)m_EventList.size(); }

	void SetSpeed(float _f) { m_fSpeed = _f; }

	void SetLookAt(Vec2 _vLookAt) { m_vLookAt = _vLookAt; }
	void InitLookAt(Vec2 _vLookAt)
	{
		m_vPrevLookAt = _vLookAt;
		m_vCurLookAt = _vLookAt;
		m_vLookAt = _vLookAt;
	}
	void SetCameraLimit(Vec2 _vLimit) { m_vCameraLimit = _vLimit; }
	void SetCameraLimitLT(Vec2 _vLimit) { m_vCameraLimitLT = _vLimit; }
	void SetLookAtOffset(Vec2 _vOffset) { m_vLookAtOffset = _vOffset; }
	void SetLookAtOffsetX(float _f) { m_vLookAtOffset.x = _f; }
	void SetLookAtOffsetY(float _f) { m_vLookAtOffset.y = _f; }
	void FixLookAt() { m_pTarget = nullptr;	m_vLookAt = m_vCurLookAt; }
	void SetTarget(CObj* _pTarget);



public:
	void tick();
	void render(HDC _dc);

public:
	void FadeIn(float _time, LEVEL_TYPE _eLevelType = LEVEL_TYPE::END)
	{
		FCamEvent evnt = {};
		evnt.Type = CAM_EFFECT::FADE_IN;
		evnt.AccTime = 0.f;
		evnt.Duration = _time;
		evnt.NextLevel = _eLevelType;

		m_EventList.push_back(evnt);
	}

	void FadeOut(float _time, LEVEL_TYPE _eLevelType = LEVEL_TYPE::END)
	{
		FCamEvent evnt = {};
		evnt.Type = CAM_EFFECT::FADE_OUT;
		evnt.AccTime = 0.f;
		evnt.Duration = _time;
		evnt.NextLevel = _eLevelType;
		m_EventList.push_back(evnt);
	}

	void Shake(float _fTime, float _fShakeIntensity)
	{
		m_fShakeIntensity = _fShakeIntensity;

		FCamEvent evnt = {};
		evnt.Type = CAM_EFFECT::SHAKE;
		evnt.AccTime = 0.f;
		evnt.Duration = _fTime;
		m_EventList.push_back(evnt);
	}

	void PenitentDeath(float _time)
	{
		FCamEvent evnt = {};
		evnt.Type = CAM_EFFECT::DEATH;
		evnt.AccTime = 0.f;
		evnt.Duration = _time;
		m_EventList.push_back(evnt);
	}

	void BossClear(float _time)
	{
		m_bInEvent = true;
		m_bInClear = true;


		FCamEvent evnt = {};
		evnt.Type = CAM_EFFECT::BOSS_CLEAR;
		evnt.AccTime = 0.f;
		evnt.Duration = _time;

		m_EventList.push_back(evnt);
	}

};

