#pragma once
#include "GameObject.h"

#define PLATFORM_ANI_ID		495

#define PLATFORM_WIDTH	63
#define PLATFORM_HEIGHT	16

#define PLATFORM_SPEED_X	0.05f

#define X_LEFT_LIMIT	65
#define X_RIGHT_LIMIT	128

class CPlatform :public CGameObject
{
	float x_left;
	float x_right;
public:
	CPlatform(int ani_id,float _x_left,float _x_right) {
		this->blood = 1;
		AddAnimation(ani_id);
		vx = PLATFORM_SPEED_X;
		vy = 0;
		x_left = _x_left;
		x_right = _x_right;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	float Get_x_left() { return x_left; }
	float Get_x_right() { return x_right; }
};

