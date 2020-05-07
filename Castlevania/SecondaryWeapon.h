#pragma once
#include"Weapon.h"

#define TYPE_WEAPON_KNIFE 0
#define TYPE_WEAPON_AXE	1

#define WEAPON_GRAVITY 0.001f
#define KNIFE_SPEED 0.07f
#define AXE_SPEED_X	0.2f
#define AXE_SPEED_y	0.5f

#define KNIFE_HEIGHT 24
#define KNIFE_WIDTH	42
#define AXE_WIDTH 32
#define AXE_HEIGHT 32

class CSecondaryWeapon:public CWeapon
{
	float xBefore;// Vị trí khởi điểm của weapon
	bool isCollisonWithBrick;
public:
	CSecondaryWeapon()
	{
		isCollisonWithBrick = false;
		AddAnimation(701);
		AddAnimation(610);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void SetPosition(float x, float y);
	void SetState(int state);
	bool CheckOutCam(float x);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	//void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);

};

