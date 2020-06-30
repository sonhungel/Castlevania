#pragma once
#include "GameObject.h"
#include"Enemy.h"
#include"Define.h"

#define ENEMY_BLACK_KNIGHT_SPEED		0.05f

#define ENEMY_BLACK_KNIGHT_WIDTH		33
#define ENEMY_BLACK_KNIGHT_HEIGHT		64

#define STATE_ENEMY_BLACK_KNIGHT_EXIST		1
#define STATE_ENEMY_BLACK_KNIGHT_NOT_EXIST	0
#define STATE_ENEMY_BLACK_KNIGHT_ITEM_EXIST		2
#define STATE_ENEMY_BLACK_KNIGHT_ITEM_NOT_EXIST	3

#define ENEMY_BLACK_KNIGHT_ANI_ID	1001


class CBlackKnight :public CEnemy
{
private:

	int x_left, x_right;
public:
	CBlackKnight(float _x, float _y, int _type, int ani_id, int x_l, int x_r) :CEnemy(_x,_y)	// type for item, ani_id_item
	{
		this->type = eType::ENEMY_BLACK_KNIGHT;
		AddAnimation(ENEMY_BLACK_KNIGHT_ANI_ID);
		this->blood = 3;	// tại sao blood lại phải = 3 khi đánh 2 cái là die, 
								//vì cần blood =1 để xét item, và blood =0 để loại obj khỏi coObject
		this->state = STATE_ENEMY_BLACK_KNIGHT_EXIST;

		dt_die = 0;
		dt_strock = 0;

		vx =  ENEMY_BLACK_KNIGHT_SPEED;

		isStrock = false;

		this->x_left = x_l;
		this->x_right = x_r;

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

