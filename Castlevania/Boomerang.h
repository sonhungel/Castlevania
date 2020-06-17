#pragma once
#include "Weapon.h"
#include"Define.h"

#define BOOMERANG_HEIGHT 28
#define BOOMERANG_WIDTH 28

#define BOOMERANG_SPEED 0.5f

#define STATE_BOOMERANG_HIDE  0
#define STATE_BOOMERANG_APPEAR 1

#define BOOMERANG_SLOW_DOWN_X	0.0032f

#define BOOMERANG_TIME		2000

#define BOOMERANG_ANI_ID	605

class CBoomerang : public CWeapon
{
	static CBoomerang* __instance;
	DWORD start_attack;

	float x_left;	// giới hạn di chuyển
	float x_right;
	int turn;		// số lần quay đầu
public:
	static CBoomerang* GetInstance();
	CBoomerang();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void SetPosition(float simon_x, float simon_y);
	void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int st);
};

