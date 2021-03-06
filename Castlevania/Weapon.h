#pragma once
#ifndef __WEAPON_H_
#define __WEAPON_H_



#include"GameObject.h"
#include"Textures.h"
#include"Effect.h"
//#include"Enemy.h"
//#include"BreakBrick.h"



//=============DEFFINE=============

#define WEAPON_NOT_EXSIST 0
#define WEAPON_EXSIST 1 

#define ANIMATION_EFFECT_FIRE 800

#define STATE_SUBWEAPON_HIDE	0
#define STATE_SUBWEAPON_APPEAR	1

class CWeapon;
typedef CWeapon* LPWEAPON;

class CWeapon :public CGameObject
{protected:
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	virtual CAnimation* GetAnimation() { if (animations.size() > 0)return animation; }
};

#endif