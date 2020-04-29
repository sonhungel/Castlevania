#ifndef __SIMON_H__
#define __SIMON_H__


#pragma once

#include "GameObject.h"
#include"Whip.h"

#define SIMON_WALKING_SPEED		0.12f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_GRAVITY			0.002f

#define STATE_SIMON_IDLE			0
#define STATE_SIMON_WALKING_RIGHT	100
#define STATE_SIMON_WALKING_LEFT	200
#define STATE_SIMON_JUMP			300
#define STATE_SIMON_SIT			    400
#define STATE_SIMON_STAND_ATTACK	500
#define STATE_SIMON_SIT_ATTACK		600
#define STATE_SIMON_DIE				700
#define STATE_SIMON_UP				800
#define STATE_SIMON_ATTACK_KNIFE	900

#define ANI_SIMON_IDLE						0
#define ANI_SIMON_WALKING					1
#define ANI_SIMON_JUMPING					2
#define ANI_SIMON_SITTING					3
#define ANI_SIMON_STANDING_ATTACKING 		4
#define ANI_SIMON_SITTING_ATTACKING			5

#define ANI_SIMON_TRANS						6	// transition

#define SIMON_HEIGHT_STAND			60
#define SIMON_HEIGHT_SIT			45
#define SIMON_WIDTH					40
#define SIMON_UNTOUCHABLE_TIME		5000

#define ATTACK_TIME			100
#define TRANSITION_TIME		200
#define JUMP_TIME			0

#define ID_WEAPON_WHIP 0		// main weapon
#define ID_WEAPON_SECONDARY 1

class CSimon : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	DWORD trans_start; // Simon bất tử
	DWORD attack_start;
	vector<CWeapon*> weapons;

	static CSimon* __instance;
	int _heartCount;	// Count the number for the score, not a blood for simon
public:
	static CSimon* GetInstance();
	CSimon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	//  Cần optimize lại, hạn chế sử dụng for
	void CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj); // các item như knife,heart, whipupgrade
	//void CollisionWithBrick();
	CWhip* GetWeapon(int i = 0) { return (CWhip*)(weapons[0]); }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetTrend() { return nx; } // for the weapon
	int GetHeart() { return _heartCount; } // for HUD
};
#endif