#pragma once
#ifndef __KNIFE_H_
#define __KNIFE_H_


#include "GameObject.h"
#include "Textures.h"
#include "Weapon.h"
#include"Torch.h"
#include"Define.h"

//============DEFINE=================

#define KNIFE_HEIGHT 24
#define KNIFE_WIDTH	42

#define KNIFE_SPEED 0.5f

#define KNIFE_TIME 900
#define KNIFE_ANI_ID	701

class CKnife :public CWeapon
{

public:

	CKnife(float simon_x, float simon_y, int simon_trend)
	{

		if (simon_trend< 0)
		{
			this->x = simon_x;
		}
		else
		{
			this->x = simon_x + 20;
		}
		this->y = simon_y + 10;

		nx = simon_trend;
		vx = KNIFE_SPEED * nx;

		this->blood = 1;
		type = eType::WEAPON_KNIFE;

		AddAnimation(KNIFE_ANI_ID);
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
};

#endif