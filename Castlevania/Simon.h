#ifndef __SIMON_H__
#define __SIMON_H__


#pragma once

#include "GameObject.h"
#include"Whip.h"
#include"HidenObject.h"
#include"Define.h"

#define SIMON_WALKING_SPEED		0.15f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_GRAVITY			0.005f
#define SIMON_GRAVITY2			0.01f
#define SIMON_TREND_RIGHT		1
#define SIMON_TREND_LEFT		-1
#define SIMON_PER_STEP	8
#define SIMON_ONE_STEP	16
#define SIMON_SPEED_ON_STAIR	0.07f

#define MAX_BLOOD	16

#define STATE_SIMON_IDLE			0
#define STATE_SIMON_WALKING_RIGHT	100
#define STATE_SIMON_WALKING_LEFT	200
#define STATE_SIMON_JUMP			300
#define STATE_SIMON_SIT			    400
#define STATE_SIMON_STAND_ATTACK	500
#define STATE_SIMON_SIT_ATTACK		600
#define STATE_SIMON_DIE				700
#define STATE_SIMON_UP				800
#define STATE_SIMON_ATTACK_SUBWEAPON 900
#define STATE_SIMON_GO_UP			1000
#define STATE_SIMON_GO_DOWN			1001
#define STATE_SIMON_GO_UP_ATTACK	1010
#define STATE_SIMON_GO_DOWN_ATTACK	1011
#define STATE_SIMON_IDLE_UP			1002
#define STATE_SIMON_IDLE_DOWN		1003
#define STATE_SIMON_HURT			1100

#define ANI_SIMON_IDLE						0
#define ANI_SIMON_WALKING					1
#define ANI_SIMON_JUMPING					2
#define ANI_SIMON_SITTING					3
#define ANI_SIMON_STANDING_ATTACKING 		4
#define ANI_SIMON_SITTING_ATTACKING			5
#define ANI_SIMON_TRANS						6	
#define ANI_SIMON_GO_UP 					7
#define ANI_SIMON_GO_DOWN					8
#define ANI_SIMON_HURT						9
#define ANI_SIMON_IDLE_UP					10
#define ANI_SIMON_IDLE_DOWN					11
#define ANI_SIMON_DIE						12
#define ANI_SIMON_GO_UP_ATTACK				13
#define ANI_SIMON_GO_DOWN_ATTACK			14


#define SIMON_HEIGHT_STAND			62
#define SIMON_HEIGHT_SIT			47
#define SIMON_WIDTH					33

#define SIMON_HEIGHT_DIE			33
#define SIMON_WIDTH_DIE				60

#define SIMON_UNTOUCHABLE_TIME		1500
#define SIMON_HURT_TIME			300		// thười gian đo để ani_simon hurt

#define ATTACK_TIME			300
#define ATTACK_TIME_WAIT	1000

#define TRANSITION_TIME		500

#define TIME_FOR_ONE_STEP	200	// thời gian 2 frame

#define ID_SUB_WEAPON_IN_SIMON_KNIFE		0
#define ID_SUB_WEAPON_IN_SIMON_AXE			1
#define ID_SUB_WEAPON_IN_SIMON_BOOMERANG	2
#define ID_SUB_WEAPON_IN_SIMON_HOLLYWATER	3

class CSimon : public CGameObject
{
	static CSimon* __instance;

	bool untouchable;
	DWORD untouchable_start;
	DWORD trans_start; // Simon nhấp nháy

	DWORD attack_start;
	DWORD attack_start_temp;

	CWhip* whip;

	vector<CWeapon*> listSubWeapon;

	// Các biến sử dụng cho logic thang
	int isCanOnStair;	// 0 is idle, 1 is go UP, -1 is go DOWN
	
	bool isBeingOnStair;
	bool isAutoGo;
	int _stairTrend;	// -1 = left, 1 = right

	float x_new = 0;
	float y_new = 0;

	//=====scene=========
	int idScene_current;
	int idScene_next;
	//

	int _score;
	int _heart;
	int _live;

	int subWeapon;

	bool isSimonOnGround;

	//int SetFrameForWhip;
	
public:
	static CSimon* GetInstance();
	CSimon();

	bool isSimonOnAir;

	

	bool isCanAttack;

	int auto_x;

	bool isGoUp; // set simon ở vị trí thang đặc biệt
	bool isGoDown;
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	
	void CollisionWithItem( vector<LPGAMEOBJECT>& listObj); // các item như knife,heart, whipupgrade

	void CollisionWithBrick(DWORD dt, LPGAMEOBJECT brick, float min_tx0, float min_ty0, int nx0, int ny0,
																		float rdx0,float rdy0);

	void CollisionWithHidenObject(DWORD dt, vector<LPGAMEOBJECT>& listHidenObj);// dùng cho kết thúc thang

	void CollisionWithPlatform(DWORD dt, LPGAMEOBJECT listPlf, float min_tx0, float min_ty0, int nx0, int ny0,
																			float rdx0, float rdy0);
	void CollisionWithEnemy(DWORD dt,vector<LPGAMEOBJECT>& listObj);

	void CollisionWithPortal(DWORD dt, vector<LPGAMEOBJECT>& listObj);

	void CollisionWithObjectHaveItem(DWORD dt, vector<LPGAMEOBJECT>& listObj);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int GetTrend() { return nx; } 

	void IsCanOnStair(vector<LPGAMEOBJECT>& listObj);	// bùng cho việc bắt đầu leo lên thang 

	void SetBeingOnStair(bool onStair) { this->isBeingOnStair = onStair; }
	void SetStairTrend(int stairTrend) { this->_stairTrend = stairTrend; }
	void SetSimonOnAir(bool onAir) 
	{
		if (onAir)
			isSimonOnAir = true;
		else
			isSimonOnAir = false;
	}

	bool IsBeingOnStair() { return isBeingOnStair; } 
	int GetStairTrend() { return _stairTrend; }
	int GetIsCanOnStair() { return isCanOnStair; }
	void CalculateAutoGo();	// xác định lại hướng simon cần di chuyển để phù hợp cho vị trí auto go

	bool IsAttacking() 
	{ 
		if (attack_start > 0)
			return true; 
		return false; 
	}

	// function for score, bla bla.....
	int GetScore() { return _score; }
	int GetHeart() { return _heart; }
	int GetLive() { return _live; }

	int GetWeapon() { return subWeapon; }
	void SetWeapon(int wp) { subWeapon = wp; }

	void LoadSubWeapon(int subwp);
};
#endif