#ifndef __SIMON_H__
#define __SIMON_H__


#pragma once

#include "GameObject.h"
#include"Whip.h"
#include"HidenObject.h"
#include"Define.h"

#define SIMON_WALKING_SPEED		0.3f
#define SIMON_JUMP_SPEED_Y		0.6f
#define SIMON_GRAVITY			0.002f
#define SIMON_TREND_RIGHT		1
#define SIMON_TREND_LEFT		-1
#define SIMON_PER_STEP	8
#define SIMON_SPEED_ON_STAIR	1.23f

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

#define SIMON_UNTOUCHABLE_TIME		5000

#define ATTACK_TIME			100
#define TRANSITION_TIME		400
#define JUMP_TIME			0
#define TIME_FOR_ONE_STEP	200	// thời gian 2 frame

#define ID_WEAPON_KNIFE	0
#define ID_WEAPON_AXE 1

class CSimon : public CGameObject
{
	static CSimon* __instance;

	int untouchable;
	DWORD untouchable_start;
	DWORD trans_start; // Simon nhấp nháy
	DWORD stair_start;

	CWhip* whip;

	// Các biến sử dụng cho logic thang
	int isCanOnStair;	// 0 is idle, 1 is go UP, -1 is go DOWN
	//bool isHave3Direction; // dùng cho hidenObj đặc biệt
	
	bool isBeingOnStair;
	bool isAutoGo;
	int _stairTrend;	// -1 = left, 1 = right

	float new_x;
	float new_y;

	//=====scene=========
	int idScene_current;
	int idScene_next;
	//

	int _score;
	int _heart;
	int _live;
	
public:
	static CSimon* GetInstance();
	CSimon();

	int auto_x;

	bool isGoUp; // set simon ở vị trí thang đặc biệt
	bool isGoDown;
	int subWeapon;

	// Biến liên quan đến scene


	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	
	void CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj); // các item như knife,heart, whipupgrade

	void CollisionWithBrick(DWORD dt, vector<LPGAMEOBJECT>& listBrick, float min_tx0, float min_ty0, int nx0, int ny0,
																		float rdx0,float rdy0);

	void CollisionWithTorch(DWORD dt, vector<LPGAMEOBJECT>& listTorch, float min_tx0, float min_ty0, int nx0, int ny0, 
																		float rdx0, float rdy0);

	void CollisionWithHidenObject(DWORD dt, vector<LPGAMEOBJECT>& listHidenObj, float min_tx0, float min_ty0, int nx0, int ny0,
																			float rdx0, float rdy0);// dùng cho kết thúc thang

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetTrend() { return nx; } // for the weapon

	void IsCanOnStair(vector<LPGAMEOBJECT>& listObj);	// bùng cho việc bắt đầu leo lên thang

	//bool IsCanGo3DirectionOnStair() { return isHave3Direction; }

	void SetBeingOnStair(bool onStair) { this->isBeingOnStair = onStair; }
	void SetStairTrend(int stairTrend) { this->_stairTrend = stairTrend; }
	//void SetIsCanOnStair(int _isCanOnStair) { this->isCanOnStair = _isCanOnStair; }
	//void SetAutoGo(bool _autoGo) { this->isAutoGo = _autoGo; }

	bool IsBeingOnStair() { return isBeingOnStair; } 
	int GetStairTrend() { return _stairTrend; }
	void CalculateAutoGo();	// xác định lại hướng simon cần di chuyển để phù hợp cho vị trí auto go

	// function for score, bla bla.....
	int GetScore() { return _score; }
	int GetHeart() { return _heart; }
	int GetLive() { return _live; }
};
#endif