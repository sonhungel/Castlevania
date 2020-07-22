#pragma once
#include "GameObject.h"


#define GRAVITY	0.002f

class CEffectBrick : public CGameObject
{
public:
	CEffectBrick(float _x, float _y, int ani_id,int id)
	{
		this->x = _x;
		this->y = _y;
		AddAnimation(ani_id);

		switch (id)
		{
		case 0:
			vx = 0.07f;
			vy = -0.3f;
			break;
		case 1:
			vx = -0.07f;
			vy = -0.3f;
			break;
		case 2:
			vx = -0.04f;
			vy = -0.1f;
			break;
		case 3:
			vx = 0.04f;
			vy = -0.1f;
			break;
		}
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

