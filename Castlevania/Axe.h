#pragma once
#include "Weapon.h"

#define AXE_WIDTH	32
#define AXE_HEIGHT	32

#define AXE_SPEED_X	0.4f
#define AXE_SPEED_Y	0.5f

#define GRAVITY	0.002f

#define AXE_TIME	900

#define AXE_ANI_ID	603


class CAxe : public CWeapon
{

public:

	CAxe(float simon_x, float simon_y, int simon_trend);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);

	CAnimation* GetAnimation() { if (animations.size() > 0)return animation; }
};

