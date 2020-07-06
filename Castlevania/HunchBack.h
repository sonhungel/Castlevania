#pragma once
#include "Enemy.h"
#include"Game.h"

#define ENEMY_HUNCHBACK_WIDTH	34
#define ENEMY_HUNCHBACK_HEIGHT	34

#define HUNCHBACK_SPEED_X 0.06f
#define HUNCHBACK_SPEED_Y 0.06f

#define ENEMY_HUNCHBACK_ANI_ID	1005

#define STATE_ENEMY_HUNCHBACK_EXIST				1
#define STATE_ENEMY_HUNCHBACK_NOT_EXIST			0
#define STATE_ENEMY_HUNCHBACK_ITEM_EXIST		2
#define STATE_ENEMY_HUNCHBACK_ITEM_NOT_EXIST	3

#define ENEMY_HUNCHBACK_TIME_JUMP	2000

class CHunchBack :public CEnemy
{
	LPGAMEOBJECT target;		//==> this is simon

	DWORD dt_Jump;		// đo thời gian cho mỗi lần nhảy
public:
	CHunchBack(float _x, float _y, int _type, int ani_id, LPGAMEOBJECT _target) :CEnemy(_x, _y)
	{
		type = eType::ENEMY_HUNCH_BACK;
		this->target = _target;
		AddAnimation(ENEMY_HUNCHBACK_ANI_ID);


		this->blood = 2;	// tại sao blood lại phải = 2 khi đánh 1 cái là die, 
							//vì cần blood =1 để xét item, và blood =0 để loại obj khỏi coObject
		this->state = STATE_ENEMY_HUNCHBACK_EXIST;

		dt_die = 0;
		dt_strock = 0;

		isStrock = false;
		nx = 1;

		effectDie = new CEffect(DEATH_EFFECT_ANI_ID, this->x, this->y);
		effectHit = new CEffect(HIT_EFFECT_ANI_ID, this->x, this->y);

		if (type == eType::ITEM_SMALLHEART)
			item = new CItemSmallHeart(x, y);
		else if (type == eType::ITEM_RED_MONEY ||
			type == eType::ITEM_YELLOW_MONEY ||
			type == eType::ITEM_PURPLE_MONEY ||
			type == eType::ITEM_BLUE_MONEY)
			item = new CItemMoney(x, y, type, ani_id);
		else
			item = new CItemNormal(x, y, type, ani_id);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

