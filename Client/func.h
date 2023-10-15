#pragma once

Vec2 Rotate(Vec2 _vDir, float _angle);
bool GetRotateClock(Vec2 _vDir1, Vec2 _vDir2);

template <typename T>
bool IsValid(T*& _pEntity)
{
	if (_pEntity == nullptr)
	{
		return false;
	}

	if (_pEntity->IsDead())
	{
		_pEntity = nullptr;
		return false;
	}

	return true;
}

void ChangeLevel(LEVEL_TYPE _eType);

void SaveWString(const wstring& _str, FILE* _File);
void LoadWString(wstring& _str, FILE* _File);