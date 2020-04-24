#pragma once
#ifndef __WEAPON_H_
#define __WEAPON_H_
#include"GameObject.h"
#include"Textures.h"



//=============DEFFINE=============

#define WEAPON_NOT_EXSIST 0
#define WEAPON_EXSIST 1 


class CWeapon :public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
};

#endif