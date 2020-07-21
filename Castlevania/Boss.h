#pragma once
#include "Enemy.h"
#include"Simon.h"

#define BOSS_WIDTH  100
#define BOSS_HEIGHT 50

#define BOSS_MAX_BLOOD  16

#define BOSS_ANI_SLEEPING  0
#define BOSS_ANI_FLYING	   1

#define STATE_BOSS_NOT_EXSIST		0
#define STATE_BOSS_ITEM				1
#define STATE_BOSS_ITEM_NOT_EXSIST 	2
#define STATE_BOSS_SLEEP			3
#define STATE_BOSS_FLY				4

#define TIME_BOSS_ATTACK	10000
#define TIME_BOSS_CHECK_FLY 3000
#define TIME_BOSS_ATTACK2 300

#define TIME_BOSS_CURVE 2000

#define BOSS_RANDOM_X1 5430
#define BOSS_RANDOM_Y1 210
#define BOSS_RANDOM_X2 5150
#define BOSS_RANDOM_Y2 210

#define BOSS_SPEED_AUTO_FLY_X 0.4f
#define BOSS_SPEED_AUTO_FLY_Y 0.3f

#define BOSS_SPEED_STRAIGHT		0.3f

#define TIME_RATE 0.00005f

#define TYPE_FLY_STRAIGHT	1
#define TYPE_FLY_CURVE	2

class CBoss : public CEnemy
{
	static CBoss* __instance;

	DWORD start_attack;

	DWORD start_fly;
	DWORD start_curve;

	// Cần 3 điểm để có thể hoạt động  Bézier curve											*p2
	D3DXVECTOR2 position0;	//vị trí đầu							*p0                  ..
	D3DXVECTOR2 position1;	// chọn lựa từ vị trí simon				  ..			   ..
	D3DXVECTOR2 position2;	// vị trí di chuyện tới						..	      .  ..
																		  //..*p1-simon	

	int step;
	int typeMove;	// loại chuyển động	thẳng hoặc curve	1 là bay thẳng, 2 là bay curve

	D3DXVECTOR2 startPosition;	// vị trí ban đầu khi chưa đánh simon

public:

	bool isActive;
	static CBoss* GetInstance();

	CBoss(float _x, float _y):CEnemy(_x,_y)
	{
		this->type = eType::ENEMY_RAVEN;

		this->blood = BOSS_MAX_BLOOD + 1;	// thêm 1 để thể hiện trạng thái tồn tại	bên trong HUD phải trừ 1
		this->state = STATE_BOSS_SLEEP;

		dt_die = 0;
		dt_strock = 0;

		vx = vy = 0;

		isStrock = false;
		nx = 1;

		effectDie = new CEffect(DEATH_EFFECT_ANI_ID, this->x, this->y);
		effectHit = new CEffect(HIT_EFFECT_ANI_ID, this->x, this->y);

		item = new CItemNormal(x, y, ITEM_BOSSBALL);
		
		startPosition = D3DXVECTOR2(x, y);
	
		isActive = false;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	//====== Logic move =============
	// 4 hàm tượng trưng cho 4 trạng thái bay của boss 
	// fly bình thường
	// fly tấn công lao vào simon
	// fly thẳng
	// fly curve

	void AutoFly(float next_x, float next_y);
	void AutoAttack(float next_x, float next_y);
	void FlyStraight(float next_x, float next_y);
	void FlyCurve(float next_x, float next_y);
	
	void SetFly();

	// tìm kiếm tại
	// https://stackoverflow.com/questions/785097/how-do-i-implement-a-b%C3%A9zier-curve-in-c
	int getPt(int n1, int n2, float perc)
	{
		int diff = n2 - n1;

		return n1 + (diff * perc);
	}

	void Reset();

	void BossActive() { isActive = true; }
};