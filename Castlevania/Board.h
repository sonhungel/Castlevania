#pragma once
#include"Game.h"
#include"GameObject.h"
#include "Simon.h"
#include"Weapon.h"
#include"Code.h"
#include"Knife.h"
#include"Boss.h"

#define SUBWEAPON_KNIFE_ID 0 

class CBoard
{
	int _time;
	int _weapon;
	DWORD _count;
	bool isStop;
	CCode* code;
	int number;		// item II, item III
	DWORD timeItem;
	static CBoard* __instance;

	LPGAMEOBJECT boss;
public:
	CBoard()
	{
		_time = 300;
		_count = GetTickCount();
		isStop = false;
		_weapon = 0;
		number = 0;
		code = new CCode();
		timeItem = 0;
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
	void ChangeWeapon();

	void SetNumber(int nb)
	{
		this->number = nb;
		timeItem = GetTickCount();
	}

	void SetBossToHUD(LPGAMEOBJECT _boss) { this->boss = _boss; }

	void SetBossDeadth()
	{
		if (boss != NULL)
			boss->blood = 1;
	}
};

