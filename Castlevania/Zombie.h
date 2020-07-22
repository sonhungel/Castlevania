#pragma once
#include "Enemy.h"

#define ENEMY_ZOMBIE_WIDTH		32
#define ENEMY_ZOMBIE_HEIGHT		63

#define ENEMY_ZOMBIE_SPEED			0.05f
#define ENEMY_ZOMBIE_GRAVITY		0.04f


#define ENEMY_ZOMBIE_ANI_ID			1000

#define X_LEFT_LIMIT	890

class CZombie :public CEnemy
{
public:
	CZombie(float _x, float _y, int _typeitem, int _trend) :CEnemy(_x, _y) // type for item, ani_id_item
	{
		this->type = eType::ENEMY_ZOMBIE;

		this->blood = 2;	// Chỉ sống = 1 hit
		AddAnimation(ENEMY_ZOMBIE_ANI_ID);
		
		this->state = STATE_ENEMY_EXIST;

		this->nx = _trend;
		vx = nx*ENEMY_ZOMBIE_SPEED;

		isStrock = false;

		effectDie = new CEffect(DEATH_EFFECT_ANI_ID, this->x, this->y);
		effectHit = new CEffect(HIT_EFFECT_ANI_ID, this->x, this->y);

		if (_typeitem == eType::ITEM_SMALLHEART)
			item = new CItemSmallHeart(x, y);
		else if (_typeitem == eType::ITEM_RED_MONEY ||
			_typeitem == eType::ITEM_YELLOW_MONEY ||
			_typeitem == eType::ITEM_PURPLE_MONEY ||
			_typeitem == eType::ITEM_BLUE_MONEY)
			item = new CItemMoney(x, y, _typeitem);
		else
			item = new CItemNormal(x, y, _typeitem);
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

