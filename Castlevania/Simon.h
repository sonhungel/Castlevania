#ifndef __SIMON_H__
#define __SIMON_H__


#pragma once

#include "GameObject.h"
#include"WhipNormal.h"



//============DEFINE=============

#define SIMON_WALKING_SPEED		0.12f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_GRAVITY			0.002f
//============STATE==============
#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_SIT			    400
#define SIMON_STATE_STAND_ATTACK	500
#define SIMON_STATE_SIT_ATTACK		600
#define SIMON_STATE_DIE				700
#define SIMON_STATE_UP				800
//#define SIMON_STATE_ATTACK_KNIFE	900

//===========ANIMATION============
#define SIMON_ANI_IDLE						0
#define SIMON_ANI_WALKING					1
#define SIMON_ANI_JUMPING					2
#define SIMON_ANI_SITTING					3
#define SIMON_ANI_STANDING_ATTACKING 		4
#define SIMON_ANI_SITTING_ATTACKING			5
//#define SIMON_ANI_KNIFE					6
#define SIMON_ANI_TRANS						6	// transition

//================================
#define SIMON_HEIGHT_STAND			60
#define SIMON_HEIGHT_SIT			45
#define SIMON_WIDTH					40
#define SIMON_UNTOUCHABLE_TIME		5000
//=============COUNTING============
#define ATTACK_TIME			100
#define JUMP_TIME			0

//===========ID WEAPON---------
#define ID_WEAPON_VAMPIREKILLER		0
#define ID_WEAPON_DAGGER			1


class CSimon : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	DWORD trans_start; // Simon bất tử
	DWORD attack_start;
	vector<CWeapon*> weapons;
	static CSimon* __instance;
	int _heart;
public:
	static CSimon* GetInstance();
	CSimon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	CWhipNormal* GetWeapon(int i = 0) { return (CWhipNormal*)(weapons[0]); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetTrend() { return nx; }
	int GetHeart() { return _heart; }
	void SetHeart(int heart) { _heart = heart; }
};
#endif