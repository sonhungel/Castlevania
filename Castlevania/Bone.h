#pragma once
#include "GameObject.h"
#include"Define.h"

#define BONE_ANI_ID	1100

#define BONE_WIDTH	33
#define BONE_HEIGHT	33

#define BONE_GRAVITY	0.001f

#define BONE_SPEED_X		0.15f
#define BONE_SPEED_Y		0.45f

#define STATE_BONE_APPEAR	1
#define STATE_BONE_HIDE		0


class CBone :public CGameObject
{

public:
	CBone(float _x, float _y, int trend)
	{
		this->blood = 1;

		AddAnimation(BONE_ANI_ID);

		this->state = STATE_BONE_APPEAR;

		this->nx = trend;

		this->x = _x + 5;
		this->y = _y + 5;

		vx = nx * BONE_SPEED_X;
		vy = -BONE_SPEED_Y;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

