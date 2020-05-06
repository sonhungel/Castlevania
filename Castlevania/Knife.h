#pragma once
#ifndef __KNIFE_H_
#define __KNIFE_H_


#include "GameObject.h"
#include "Textures.h"
#include "Weapon.h"
#include"Torch.h"

//============DEFINE=================

#define KNIFE_HEIGHT 24
#define KNIFE_WIDTH	42

#define KNIFE_EXSIST	1
#define KNIFE_NOT_EXSIST	0

#define KNIFE_SPEED 0.1f

#define STATE_KNIFE_APPEAR 1
#define STATE_KNIFE_HIDE 0

#define KNIFE_TIME 900

class CKnife :public CWeapon
{
	static CKnife* __instance;
	DWORD start_attack;
public:

	static CKnife* GetInstance();
	CKnife()
	{
		vx = KNIFE_SPEED;
		AddAnimation(701);
		start_attack = 0;
		state = STATE_KNIFE_HIDE;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void SetPosition(float x, float y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
};

#endif