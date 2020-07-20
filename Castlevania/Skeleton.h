#pragma once
#include "Enemy.h"
#include"Bone.h"

#define ENEMY_SKELETON_ANI_ID	1009

#define ENEMY_SKELETON_SPEED_X	0.13f
#define ENEMY_SKELETON_SPEED_Y	0.45f

#define ENEMY_SKELETON_WIDTH	34
#define ENEMY_SKELETON_HEIGHT	66

#define STATE_ENEMY_SKELETON_ACTIVE	1
#define STATE_ENEMY_SKELETON_IDLE	0

#define DISTANCE_SKELETON_ACTIVE		240

#define DISTANCE_SKELETON_WALK_OUT_OF_SIMON	64
#define DISTANCE_SKELETON_WALK_TO_SIMON		160	

#define ENEMY_SKELETON_GRAVITY 0.0015f


class CSkeleton :public CEnemy
{
	bool isJump, wasTouchBrick;

	vector<LPGAMEOBJECT> listBone;

	LPGAMEOBJECT target;

	int state_temp; // chỉ dùng bên trong skeleton

	void SetSkeletonState(int state);
public:
	CSkeleton(float _x, float _y, int _typeitem,LPGAMEOBJECT _target) :CEnemy(_x, _y) // type for item, ani_id_item
	{
		this->type = eType::ENEMY_SKELETON;
		this->target = _target;

		this->blood = 2;	// Chỉ sống = 1 hit
		AddAnimation(ENEMY_SKELETON_ANI_ID);

		this->state = STATE_ENEMY_EXIST;

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

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	vector<LPGAMEOBJECT> GetListBone() { return listBone; }

};
