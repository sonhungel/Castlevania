#pragma once
#include "Enemy.h"

#define ENEMY_RAVEN_WIDTH		34
#define ENEMY_RAVEN_HEIGHT		34

#define ENEMY_RAVEN_ANI_ID_IDLE			1007
#define ENEMY_RAVEN_ANI_ID_FLY			1008

#define ENEMY_RAVEN_ANI_IDLE	0
#define ENEMY_RAVEN_ANI_FLY		1


#define STATE_ENEMY_RAVEN_IDLE		0		// chỉ sử dụng bên trong ra ven để xử lý các logic di chuyển, cũng như animation
#define STATE_ENEMY_RAVEN_FLY		1

#define ENEMY_RAVEN_SPEED_NORMAL	2.0f
#define ENEMY_RAVEN_SPEED_BUFF		3.5f

#define RAVEN_TIME_WAIT_TO_ATTACK		1500
#define RAVEN_TIME_WAIT		1000

#define DISTANCE_FROM_SIMON_TO_TARGET_FIRST		70

class CRaven :public CEnemy
{
	// đầu tiên raven sẽ di chuyển với tốc độ bình thường khi tới targetFirst, sau 1 thời gian chờ cố định
	// raven sẽ lao vào target simon
	

	LPGAMEOBJECT simon;	// => simon

	D3DXVECTOR2 targetFirst;	// vị trí raven cần di chuyển đến lần đầu

	DWORD dt_wait;
	DWORD dt_waitAttack;

	// random vị trí x y cộng thêm simon_position để lấy position đầu

	bool ravenActive;
	bool switchTargetToSimon;
	bool isBuffSpeed;		// tăng tốc khi lao vào simon

	bool isGettedPositionFirt;	// cờ đánh dấu liệu raven đã lấy đc target đầu tiên hay chưa


	//================================Không sử dụng bên ngoài ======================
	int stateTemp;	// chỉ sử dụng bên trong Raven để xử lý những logic di chuyển và animation

public :
	CRaven(float _x, float _y, int _typeitem, int ani_id, LPGAMEOBJECT _target) :CEnemy(_x, _y)
	{
		type = eType::ENEMY_RAVEN;
		this->simon = _target;

		this->blood = 2;	// tại sao blood lại phải = 2 khi đánh 1 cái là die, 
							//vì cần blood =1 để xét item, và blood =0 để loại obj khỏi coObject
		this->state = STATE_ENEMY_EXIST;

		this->stateTemp = STATE_ENEMY_RAVEN_IDLE;

		AddAnimation(ENEMY_RAVEN_ANI_ID_IDLE);
		AddAnimation(ENEMY_RAVEN_ANI_ID_FLY);

		isGettedPositionFirt = false;
		switchTargetToSimon = false;
		ravenActive = false;

		dt_die = 0;
		dt_strock = 0;

		dt_wait = 0;
		dt_waitAttack = 0;

		vx = vy = 0;

		isStrock = false;
		nx = 1;

		effectDie = new CEffect(DEATH_EFFECT_ANI_ID, this->x, this->y);
		effectHit = new CEffect(HIT_EFFECT_ANI_ID, this->x, this->y);

		if (_typeitem == eType::ITEM_SMALLHEART)
			item = new CItemSmallHeart(x, y);
		else if (_typeitem == eType::ITEM_RED_MONEY ||
			_typeitem == eType::ITEM_YELLOW_MONEY ||
			_typeitem == eType::ITEM_PURPLE_MONEY ||
			_typeitem == eType::ITEM_BLUE_MONEY)
			item = new CItemMoney(x, y, _typeitem, ani_id);
		else
			item = new CItemNormal(x, y, _typeitem, ani_id);
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void RandomPositonFirst(D3DXVECTOR2 &targetFirst);

	D3DXVECTOR2 Rada(D3DXVECTOR2 raven,D3DXVECTOR2 target,float speedOfRaven);	// dò tìm đường đi và di chuyển

	
};

