#pragma once
#include "GameObject.h"

#define EFFECT_BRICK_ANI_ID  830

#define GRAVITY	0.002f

class CEffectBrick : public CGameObject
{
public:
	CEffectBrick(float _x, float _y, int ani_id)
	{
		this->x = _x;
		this->y = _y;
		AddAnimation(ani_id);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

