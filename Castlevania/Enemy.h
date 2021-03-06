﻿#pragma once
#include "GameObject.h"
#include"Item.h"
#include"ItemMoney.h"
#include"ItemNormal.h"
#include"ItemSmallHeart.h"
#include"Effect.h"

#define TIME_EFFECT_HIT_ENEMY	100
#define TIME_EFFECT_DIE_ENEMY	300

#define STATE_ENEMY_NOT_EXIST	0
#define STATE_ENEMY_EXIST	1
#define STATE_ENEMY_ITEM_EXIST	2
#define STATE_ENEMY_ITEM_NOT_EXIST	3

#define ENEMY_GRAVITY	0.002f

class CEnemy :public CGameObject
{
private:
	bool isStop;
protected:
	DWORD dt_die; // đo thời gian cho animation lửa xuất hiện sau khi đánh 
	DWORD dt_strock;
	CItem* item;

	CEffect* effectDie;
	CEffect* effectHit;

	int ny;


public:

	bool isStrock;

	CEnemy(float _x = 0, float _y = 0)
	{
		this->x = _x;
		this->y = _y;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) = 0;
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;

	CItem* GetItem() { return item; }
};

