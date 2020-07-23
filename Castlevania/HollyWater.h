#pragma once
#include "Weapon.h"
#include"Effect.h"
#include"Define.h"

#define HOLLYWATER_HEIGHT 27
#define HOLLYWATER_WIDTH 30

#define HOLLYWATER_SPEED_X 0.3f
#define HOLLYWATER_SPEED_Y 0.4f

#define GRAVITY	0.002f

#define HOLLYWATER_TIME		1500

#define HOLLYWATER_ANI_ID	604

#define HOLLYWATER_EFFECT_ANI_ID	820


class CHollyWater : public CWeapon
{

	DWORD start_attack;

	CEffect* effect;

	bool isBroke;
public:

	CHollyWater(float simon_x, float simon_y, int simon_trend);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};