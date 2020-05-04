#pragma once
#include"Game.h"
#include"GameObject.h"
#include "Simon.h"
class CBoard
{
	int _time;
	int _weapon;
	DWORD _count;
	bool isStop;
	int _numberOfWeapon;
	static CBoard* __instance;
public:
	CBoard()
	{
		_time = 300;
		//_weapon = eType::DAGGER;
		_count = GetTickCount();
		isStop = false;
		_numberOfWeapon = 0;
		_weapon = 0;
	}
	static CBoard* GetInstance();
	void Update(DWORD dt);
	void Render();
	void TimeDown() {
		if (GetTickCount() - _count >= 1 && _time > 0)
		{
			_time--;
			_count = GetTickCount();
			

		}
	}

};

