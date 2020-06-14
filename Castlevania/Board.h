#pragma once
#include"Game.h"
#include"GameObject.h"
#include "Simon.h"
#include"Weapon.h"
#include"Code.h"
#include"Knife.h"

#define SUBWEAPON_KNIFE_ID 0 

class CBoard
{
	int _time;
	int _weapon;
	DWORD _count;
	bool isStop;
	CCode* code;
	//vector<LPWEAPON> listWeapon;
	static CBoard* __instance;
public:
	CBoard()
	{
		_time = 300;
		_count = GetTickCount();
		isStop = false;
		_weapon = 0;
		//listWeapon.push_back(CKnife::GetInstance());
		code = new CCode();
	}
	~CBoard()
	{
		if (code == NULL)
			delete code;
		code = NULL;
	}
	static CBoard* GetInstance();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void TimeDown() {
		if (GetTickCount() - _count >= 1 && _time > 0)
		{
			_time--;
			_count = GetTickCount();
		}
	}

};

