#pragma once
#include "Weapon.h"

#define AXE_WIDTH	32
#define AXE_HEIGHT	32

#define AXE_EXIST	1
#define AXE_NOT_EXIST	0

#define AXE_SPEED_X	0.4f
#define AXE_SPEED_Y	0.5f

#define AXE_STATE_HIDE	0
#define AXE_STATE_APPEAR	1

#define GRAVITY	0.002f

#define AXE_TIME	900

#define AXE_ANI_ID	603


class CAxe : public CWeapon
{
	static CAxe* __instance;
	DWORD start_attack;
public:
	static CAxe* GetInstance();
	CAxe();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetPosition(float simon_x,float simon_y);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	void SetState(int st);
};

