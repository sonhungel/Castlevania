#ifndef __WHIPNORMAL_H__

#define __WHIPNORMAL_H__

#include"GameObject.h"
#include"Weapon.h"
#include"Textures.h"

#define WHIPNORMAL_HEIGHT 64
#define WHIPNORMAL_WIDTH 160

#define WHIPNORMAL_EXSIST 1
#define WHIPNORMAL_NOT_EXSIST 0



class CWhipNormal :public CWeapon
{
	int _level; // level tượng trưng cho độ dài của Whip, 1 và 2 ngắn. 3 dài
	static CWhipNormal* __instance;
public:
	static CWhipNormal* GetInstance();
	CWhipNormal();
	void SetPosition(float simon_x, float simon_y);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void setDefaultLevel() { _level = 1; }
	void setUpLevel();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);

};
#endif // !__WHIPNORMAL_H__

