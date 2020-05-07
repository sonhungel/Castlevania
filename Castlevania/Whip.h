#ifndef __WHIP_H__

#define __WHIP_H__

#include"GameObject.h"
#include"Weapon.h"
#include"Textures.h"

//===================DEFINE===========
#define WHIPNORMAL_HEIGHT 40
#define WHIPNORMAL_WIDTH 115


#define WHIPNORMAL_EXSIST 1
#define WHIPNORMAL_NOT_EXSIST 0

#define ANI_WHIP_LEVEL_1	0
#define ANI_WHIP_LEVEL_2	1
#define ANI_WHIP_LEVEL_3	2


class CWhip :public CWeapon
{
	int _level; // level tượng trưng cho độ dài của Whip, 1 và 2 ngắn. 3 dài
	//static CWhip* __instance;
public:
	//static CWhip* GetInstance();
	CWhip();
	void SetPosition(float x, float y);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void setDefaultLevel() { _level = 1; }
	void setUpLevel();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	CAnimation* GetAnimation() { if (animations.size() > 0)return animation; }

};
#endif 

