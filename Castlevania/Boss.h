#pragma once
#include "Enemy.h"
#include"Simon.h"

#define BOSS_WIDTH  30
#define BOSS_HEIGHT 63

#define BOSS_MAX_BLOOD  16

#define BOSS_ANI_SLEEPING  0
#define BOSS_ANI_FLYING	   1


// state temp
#define STATE_BOSS_IDLE				3
#define STATE_BOSS_FLYING			4
#define STATE_BOSS_ACTIVE			5
#define STATE_BOSS_FLY_AWAY			6

#define BOSS_ANI_ID_SLEEP	1010
#define BOSS_ANI_ID_FLY		1011

#define BOSS_DEFAULT_TIME_TO_FLY		1000
#define BOSS_FAST_TIME_TO_FLY			1000
#define BOSS_STOP_TIME_WAITING			1500
#define BOSS_ATTACK_TIME_WAITING		3000

#define BOSS_EFFECT_DEATH	840
#define BOSS_TIME_EFFECT_DEATH		2100

#define BOSS_SPEED_Y 0.3f

class CBoss : public CEnemy
{

	bool isFlyToTarget = false;
	bool isFlyToSimon = false;

	float xCam;

	int flyToSimonPercent;

	D3DXVECTOR2 simonPostion;

	// 3 vị trí cần thiết để xây dựng khả năng di chuyển theo quỹ đạo curve
	D3DXVECTOR2 position0;
	D3DXVECTOR2 position1;
	D3DXVECTOR2 position2;

	int startTimeWaiting = 0;
	bool isStopWaiting = false;

	bool dropItem = false;
	bool isFlying = false;

	DWORD attackTime;;
	int state_temp;

	static bool isActive;

public:
	

	CBoss(float _x, float _y):CEnemy(_x,_y)
	{
		this->type = eType::ENEMY_BOSS;

		this->blood = BOSS_MAX_BLOOD + 1;	// thêm 1 để thể hiện trạng thái tồn tại	bên trong HUD phải trừ 1

		SetStateTemp(STATE_BOSS_IDLE);

		AddAnimation(BOSS_ANI_ID_SLEEP);
		AddAnimation(BOSS_ANI_ID_FLY);
		this->state = STATE_ENEMY_EXIST;

		dt_die = 0;
		dt_strock = 0;

		vx = vy = 0;

		isStrock = false;
		nx = 1;

		effectDie = new CEffect(BOSS_EFFECT_DEATH, this->x, this->y);
		effectHit = new CEffect(HIT_EFFECT_ANI_ID, this->x, this->y);

		item = new CItemNormal(x+35, y, ITEM_BOSSBALL);

		isFlyToTarget = false;
		isFlyToSimon = false;

		startTimeWaiting = 0;
		isStopWaiting = false;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetStateTemp(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void startAttack() { attackTime = GetTickCount(); }
	void FlyToTarget(DWORD dt, D3DXVECTOR2 target);
	void Flying(DWORD dt);
	void RandomNewPosition();

	// tìm kiếm tại
	// https://stackoverflow.com/questions/785097/how-do-i-implement-a-b%C3%A9zier-curve-in-c
	int getPt(int n1, int n2, float perc)
	{
		int diff = n2 - n1;

		return n1 + (diff * perc);
	}

	D3DXVECTOR2 Rada(D3DXVECTOR2 boss, D3DXVECTOR2 target, float speedOfRaven);	// dò tìm đường đi và di chuyển

	//void BossActive() {
	//	isActive = true;
	//	SetState(STATE_BOSS_ACTIVE);
	//}

	static void Active() { isActive= true; }
	static void Stop() { isActive = false; }
	static bool IsActive() { return isActive; }

};