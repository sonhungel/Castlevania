#pragma once
#include "Enemy.h"

#define ENEMY_ZOMBIE_WIDTH		32
#define ENEMY_ZOMBIE_HEIGHT		62

#define ENEMY_ZOMBIE_SPEED			0.05f
#define ENEMY_ZOMBIE_GRAVITY		0.04f

#define STATE_ENEMY_ZOMBIE_EXIST			1
#define STATE_ENEMY_ZOMBIE_NOT_EXIST		0
#define STATE_ENEMY_ZOMBIE_ITEM_EXIST		2
#define STATE_ENEMY_ZOMBIE_ITEM_NOT_EXIST	3

#define ENEMY_ZOMBIE_ANI_ID			1000

class CZombie :public CEnemy
{
public:
	CZombie(float _x, float _y, int _type, int ani_id, int _trend) :CEnemy(_x, _y) // type for item, ani_id_item
	{
		this->type = eType::ENEMY_ZOMBIE;

		this->blood = 2;	// Chỉ sống = 1 hit
		AddAnimation(ENEMY_ZOMBIE_ANI_ID);
		
		this->state = STATE_ENEMY_ZOMBIE_EXIST;

		this->nx = _trend;
		vx = nx*ENEMY_ZOMBIE_SPEED;

		isStrock = false;

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
			item = new CItemNormal(x, y, type, ani_id); //
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

