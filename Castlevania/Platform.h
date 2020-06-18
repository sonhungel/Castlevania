#pragma once
#include "GameObject.h"

#define PLATFORM_ANI_ID		495

#define PLATFORM_WIDTH	63
#define PLATFORM_HEIGHT	16

#define PLATFORM_SPEED_X	0.05f

class CPlatform :public CGameObject
{
	float x_left;
	float x_right;
public:
	CPlatform(int ani_id) {
		this->blood = 1;
		AddAnimation(ani_id);
		vx = PLATFORM_SPEED_X;
		x_left = 65;
		x_right = 128;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

