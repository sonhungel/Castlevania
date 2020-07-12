#pragma once
#include "GameObject.h"
#include"Enemy.h"
#include"Define.h"

#define ENEMY_BAT_SPEED_X	0.15f
#define ENEMY_BAT_SPEED_Y	0.2f

#define ENEMY_BAT_ANI_ID_IDLE	1002
#define ENEMY_BAT_ANI_ID_FLY	1003

#define ENEMY_BAT_ANI_IDLE	0
#define ENEMY_BAT_ANI_FLY	1

#define ENEMY_BAT_WIDTH 32
#define ENEMY_BAT_HEIGHT 32

#define DISTANCE_FROM_PREPOSITION_TO_BOTTOM_LIMIT	96	// đã đo trong game thực tế với khoảng cách 4 viên gạch

// => với ý tưởng này sẽ giải quyết đc bài toán khoảng cách active bat so với simon luôn luôn cố định, chỉ cần điều chỉnh position của bat cho phù hợp


#define DISTANCE_ACTIVE			170


class CBat :public CEnemy
{
private:
	float bottomLimit;

	bool isActive;

	LPGAMEOBJECT target;		//==> this is simon

public:
	CBat(float _x, float _y, int _typeitem, int ani_id,LPGAMEOBJECT _target) :CEnemy(_x, _y)
	{
		this->type = eType::ENEMY_BAT;

		AddAnimation(ENEMY_BAT_ANI_ID_IDLE);
		AddAnimation(ENEMY_BAT_ANI_ID_FLY);

		this->bottomLimit = y + DISTANCE_FROM_PREPOSITION_TO_BOTTOM_LIMIT;

		this->blood = 2;	// tại sao blood lại phải = 2 khi đánh 1 cái là die, 
							//vì cần blood =1 để xét item, và blood =0 để loại obj khỏi coObject
		this->state = STATE_ENEMY_EXIST;

		dt_die = 0;
		dt_strock = 0;

		this->target = _target;

		vx = ENEMY_BAT_SPEED_X;
		vy = ENEMY_BAT_SPEED_Y;
		nx = 1;

		isStrock = false;

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

	void SetBatDie() 
	{	if(dt_die==0)
			dt_die = GetTickCount(); }
};

